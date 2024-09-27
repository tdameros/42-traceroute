/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:04:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/09/25 16:04:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "traceroute.h"
#include "socket.h"
#include "icmp.h"
#include "time.h"
#include "flags.h"

static int32_t send_udp_probe(traceroute_t *traceroute);
static traceroute_result_t receive_icmp_probe(traceroute_t *traceroute, double start_time);
static traceroute_result_t
parse_icmp_probe(traceroute_t *traceroute, int32_t bytes_received, struct sockaddr_in reply_addr);

int8_t init_traceroute(traceroute_t *traceroute, flags_t *flags) {
  traceroute->original_host = flags->hostname;
  traceroute->ttl = flags->first_hop_value;
  traceroute->port = flags->port_value;
  traceroute->max_ttl = flags->max_hops_value;
  traceroute->max_tries = flags->tries_value;
  traceroute->wait_time = flags->wait_value;
  traceroute->udp_socket = create_udp_socket();
  if (traceroute->udp_socket < 0) {
    return -1;
  }
  set_udp_socket_broadcast(traceroute->udp_socket, true);
  set_udp_socket_timeout(traceroute->udp_socket, 1, 0);
  resolve_udp_host(traceroute->original_host, traceroute->port, &traceroute->destination);
  traceroute->icmp_socket = create_icmp_socket();
  set_icmp_socket_broadcast(traceroute->icmp_socket, true);
  set_icmp_socket_timeout(traceroute->icmp_socket, 1, 0);
  set_icmp_socket_debug(traceroute->icmp_socket, true);
  return 0;
}

void increment_port(traceroute_t *traceroute) {
  traceroute->port++;
  traceroute->destination.sin_port = htons(traceroute->port);
}

traceroute_result_t probe_traceroute(traceroute_t *traceroute) {
  double start_time = get_current_time_in_ms();
  if (send_udp_probe(traceroute) < 0) {
    return (traceroute_result_t){.status = TRACEROUTE_FATAL_ERROR};
  }
  return receive_icmp_probe(traceroute, start_time);
}

static int32_t send_udp_probe(traceroute_t *traceroute) {
  uint32_t ttl = traceroute->ttl;
  if (setsockopt(traceroute->udp_socket, IPPROTO_IP, IP_TTL, &ttl, sizeof(&ttl)) < 0) {
    return -1;
  }
  traceroute->destination.sin_port = htons(traceroute->port);
  if (sendto(traceroute->udp_socket,
             traceroute->packet,
             DEFAULT_PACKET_SIZE,
             0,
             (struct sockaddr *)&traceroute->destination,
             sizeof(traceroute->destination)) < 0) {
    fprintf(stderr, "ft_traceroute: sendto: %s\n", strerror(errno));
    return -1;
  }
  return 0;
}

static traceroute_result_t receive_icmp_probe(traceroute_t *traceroute, double start_time) {
  struct sockaddr_in reply_addr;
  socklen_t reply_addr_len = sizeof(reply_addr);
  while (get_current_time_in_ms() - start_time <= traceroute->wait_time * 1000) {
    int32_t bytes_received = recvfrom(traceroute->icmp_socket,
                                      traceroute->packet,
                                      MAX_PACKET_SIZE,
                                      0,
                                      (struct sockaddr *)&reply_addr,
                                      &reply_addr_len);
    double elapsed = get_current_time_in_ms() - start_time;
    if (bytes_received > 0) {
      traceroute_result_t result = parse_icmp_probe(traceroute, bytes_received, reply_addr);
      if (result.status == TRACEROUTE_SUCCESS || result.status == TRACEROUTE_TIME_EXCEEDED) {
        result.time = elapsed;
        return result;
      }
    }
  }
  return (traceroute_result_t){.status = TRACEROUTE_TIMEOUT};
}

static traceroute_result_t
parse_icmp_probe(traceroute_t *traceroute, int32_t bytes_received, struct sockaddr_in reply_addr) {
  traceroute_result_t result = {0};

  if (bytes_received < (int32_t)(sizeof(struct ip) + ICMP_MINLEN + sizeof(struct ip) + sizeof(in_port_t))) {
    return (traceroute_result_t){.status = TRACEROUTE_ERROR};
  }
  struct icmp *receive_icmp_header = (struct icmp *)(traceroute->packet + sizeof(struct ip));
  struct ip *ip_icmp = &receive_icmp_header->icmp_ip;
  uint8_t *udp = (uint8_t *)(traceroute->packet + sizeof(struct ip) + ICMP_MINLEN + sizeof(struct ip));
  uint16_t port = ntohs(*(uint16_t *)(udp + sizeof(in_port_t)));

  if (ip_icmp->ip_p != IPPROTO_UDP) {
    return (traceroute_result_t){.status = TRACEROUTE_ERROR};
  }
  if (port != traceroute->port) {
    return (traceroute_result_t){.status = TRACEROUTE_ERROR};
  }
  result.reply_address = reply_addr;
  if (receive_icmp_header->icmp_type == ICMP_TIMXCEED) {
    result.status = TRACEROUTE_TIME_EXCEEDED;
    return result;
  } else if (receive_icmp_header->icmp_type == ICMP_UNREACH &&
             receive_icmp_header->icmp_code == ICMP_UNREACH_PORT) {
    result.status = TRACEROUTE_SUCCESS;
    return result;
  }
  return (traceroute_result_t){.status = TRACEROUTE_ERROR};
}