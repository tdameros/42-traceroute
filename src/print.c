/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:12:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/08/18 14:12:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>

#include "flags.h"
#include "print.h"
#include "traceroute.h"

void print_traceroute_start(const traceroute_t *traceroute) {
  printf("traceroute to %s (%s), %d hops max, %d byte packets\n",
         traceroute->original_host,
         inet_ntoa(traceroute->destination.sin_addr),
         traceroute->max_ttl,
         DEFAULT_PACKET_SIZE);
}

void print_traceroute_result(const traceroute_result_t *result,
                             bool is_first_try,
                             struct sockaddr_in previous) {

  if (result->status == TRACEROUTE_TIMEOUT) {
    printf(" * ");
  } else if (result->status == TRACEROUTE_TIME_EXCEEDED || result->status == TRACEROUTE_SUCCESS) {
    const struct sockaddr_in *addr = &previous;
    if (is_first_try || addr->sin_addr.s_addr != result->reply_address.sin_addr.s_addr) {
      if (!is_first_try && addr->sin_addr.s_addr != result->reply_address.sin_addr.s_addr) {
        printf("\n     ");
      }
      char host[NI_MAXHOST];
      int32_t result_code = getnameinfo((struct sockaddr *)&result->reply_address,
                                        sizeof(result->reply_address),
                                        host,
                                        NI_MAXHOST,
                                        NULL,
                                        0,
                                        0);
      if (result_code < 0) {
        printf(" %s (%s)",
               inet_ntoa(result->reply_address.sin_addr),
               inet_ntoa(result->reply_address.sin_addr));
      } else {
        printf(" %s (%s)", host, inet_ntoa(result->reply_address.sin_addr));
      }
    }
    printf(" %.3f ms ", result->time);
  }
}

void print_help(const char *binary_name) {
  printf("Usage: %s [OPTION...] HOST\n", binary_name);
  printf("  -f, --first-hop=NUM   Set initial hop distance, i.e., time-to-live\n");
  printf("  -m, --max-hops=NUM    Set maximal hop count (default: 64)\n");
  printf("  -p, --port=PORT       Use destination PORT port (default: 33434)\n");
  printf("  -q, --tries=NUM       Send NUM probe packets per hop (default: 3)\n");
  printf("  -w, --wait=NUM        Wait NUM seconds for response (default: 3)\n");
  printf("  -?, --help            Give this help list\n");
  printf("      --usage           Give a short usage message\n");
}

void print_usage(const char *binary_name) {
  printf("Usage: %s [-?] [-f NUM] [-m NUM] [-p PORT]\n"
         "               [-q NUM] [-w NUM] HOST\n",
         binary_name);
}