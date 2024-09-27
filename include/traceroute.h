/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:01:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/09/25 16:01:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACEROUTE_H
#define TRACEROUTE_H

#include <netinet/ip_icmp.h>
#include <stdint.h>

#include "flags.h"

#define MAX_PACKET_SIZE 1024
#define DEFAULT_PACKET_SIZE 40

typedef struct {
  uint8_t packet[MAX_PACKET_SIZE];
  char *original_host;
  struct sockaddr_in destination;
  int32_t udp_socket;
  int32_t icmp_socket;
  uint16_t port;
  uint8_t ttl;
  uint8_t max_tries;
  uint8_t max_ttl;
  uint8_t wait_time;
} traceroute_t;

typedef enum {
  TRACEROUTE_SUCCESS,
  TRACEROUTE_TIMEOUT,
  TRACEROUTE_ERROR,
  TRACEROUTE_FATAL_ERROR,
  TRACEROUTE_UNKNOWN_HOST,
  TRACEROUTE_TIME_EXCEEDED,
} traceroute_status_t;

typedef struct {
  traceroute_status_t status;
  double time;
  struct sockaddr_in reply_address;
} traceroute_result_t;

int8_t init_traceroute(traceroute_t *traceroute, flags_t *flags);
void increment_port(traceroute_t *traceroute);
traceroute_result_t probe_traceroute(traceroute_t *traceroute);
#endif