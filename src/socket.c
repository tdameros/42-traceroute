/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:00:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/08/11 19:00:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <netdb.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>

#include "socket.h"
#include "utils.h"

int32_t create_icmp_socket(void) { return (socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)); }

int32_t set_icmp_socket_timeout(int32_t socketfd, uint32_t seconds, uint32_t microseconds) {
  struct timeval timeout = {seconds, microseconds};
  int32_t return_code;

  return_code = setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
  if (return_code < 0) {
    return return_code;
  }
  return setsockopt(socketfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
}

int32_t set_icmp_socket_debug(int32_t socketfd, bool is_debug) {
  uint32_t option = is_debug;
  return setsockopt(socketfd, SOL_SOCKET, SO_DEBUG, &option, sizeof(option));
}

int32_t set_icmp_socket_broadcast(int32_t socketfd, bool is_broadcast) {
  uint32_t option = is_broadcast;
  return setsockopt(socketfd, SOL_SOCKET, SO_BROADCAST, &option, sizeof(option));
}

int32_t resolve_udp_host(char *hostname, uint16_t port, struct sockaddr_in *address) {
  struct addrinfo hints;
  struct addrinfo *res;
  ft_memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;

  int32_t status = getaddrinfo(hostname, NULL, &hints, &res);
  if (status != 0) {
    return -1;
  }
  ft_memcpy(address, res->ai_addr, sizeof(struct sockaddr_in));
  address->sin_port = htons(33434);
  (void)port;
  return 0;
}

int32_t create_udp_socket(void) { return (socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)); }

int32_t set_udp_socket_timeout(int32_t socketfd, uint32_t seconds, uint32_t microseconds) {
  struct timeval timeout = {seconds, microseconds};
  int32_t return_code;

  return_code = setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
  if (return_code < 0) {
    return return_code;
  }
  return setsockopt(socketfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
}

int32_t set_udp_socket_debug(int32_t socketfd, bool is_debug) {
  uint32_t option = is_debug;
  return setsockopt(socketfd, SOL_SOCKET, SO_DEBUG, &option, sizeof(option));
}

int32_t set_udp_socket_broadcast(int32_t socketfd, bool is_broadcast) {
  uint32_t option = is_broadcast;
  return setsockopt(socketfd, SOL_SOCKET, SO_BROADCAST, &option, sizeof(option));
}
