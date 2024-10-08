/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:12:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/08/27 22:12:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "flags.h"
#include "ft_getopt_long.h"
#include "print.h"
#include "utils.h"

#define ERROR_MSG_TRY_HELP                                                                         \
  "Try 'ft_traceroute --help' or 'ft_traceroute --usage' for more information."

static int8_t convert_arg_to_i32(const char *str, int32_t *result);

int8_t parse_flags(int argc, char *argv[], flags_t *flags) {
  int ft_opt;
  int option_index = 0;

  struct ft_option long_options[] = {{"help", ft_no_argument, 0, '?'},
                                     {"usage", ft_no_argument, 0, 'u'},
                                     {"first-hop", ft_required_argument, 0, 'f'},
                                     {"max-hops", ft_required_argument, 0, 'm'},
                                     {"port", ft_required_argument, 0, 'p'},
                                     {"tries", ft_required_argument, 0, 'q'},
                                     {"wait", ft_required_argument, 0, 'w'},
                                     {0, 0, 0, 0}};
  flags->first_hop_value = DEFAULT_FIRST_HOP;
  flags->max_hops_value = DEFAULT_MAX_HOPS;
  flags->port_value = DEFAULT_PORT;
  flags->tries_value = DEFAULT_TRIES;
  flags->wait_value = DEFAULT_WAIT;
  int32_t value;

  while ((ft_opt = ft_getopt_long(argc, argv, "?huf:m:p:q:w:", long_options, &option_index)) !=
         -1) {
    switch (ft_opt) {
    case '?':
      print_help(argv[0]);
      return 0;
    case 'u':
      print_usage(argv[0]);
      return 0;
    case 'f':
      if (convert_arg_to_i32(ft_optarg, &value) < 0 || value <= 0 || value > MAX_FIRST_HOP) {
        fprintf(stderr, "ft_traceroute: invalid value (`%s')\n", ft_optarg);
        return -1;
      }
      flags->first_hop_value = value;
      flags->options.first_hop = true;
      break;
    case 'q':
      if (convert_arg_to_i32(ft_optarg, &value) < 0 || value <= 0 || value > MAX_TRIES) {
        fprintf(stderr, "ft_traceroute: invalid value (`%s')\n", ft_optarg);
        return -1;
      }
      printf("value: %d\n", value);
      flags->tries_value = value;
      flags->options.tries = true;
      break;
    case 'm':
      if (convert_arg_to_i32(ft_optarg, &value) < 0 || value <= 0 || value > MAX_MAX_HOPS) {
        fprintf(stderr, "ft_traceroute: invalid value (`%s')\n", ft_optarg);
        return -1;
      }
      flags->max_hops_value = value;
      flags->options.max_hops = true;
      break;
    case 'p':
      if (convert_arg_to_i32(ft_optarg, &value) < 0 || value <= 0 || value > MAX_PORT) {
        fprintf(stderr, "ft_traceroute: invalid value (`%s')\n", ft_optarg);
        return -1;
      }
      flags->port_value = value;
      flags->options.port = true;
      break;
    case 'w':
      if (convert_arg_to_i32(ft_optarg, &value) < 0 || value <= 0 || value > MAX_WAIT) {
        fprintf(stderr, "ft_traceroute: invalid value (`%s')\n", ft_optarg);
        return -1;
      }
      flags->wait_value = value;
      flags->options.wait = true;
      break;
    default:
      fprintf(stderr, ERROR_MSG_TRY_HELP "\n");
      return -1;
    }
  }

  if (ft_optind < argc) {
    flags->hostname = argv[ft_optind];
    return 1;
  } else {
    fprintf(stderr, "ft_traceroute: missing host operand\n");
    fprintf(stderr, ERROR_MSG_TRY_HELP "\n");
    return -1;
  }
}

static int8_t convert_arg_to_i32(const char *str, int32_t *result) {

  errno = 0;
  int32_t val = ft_atoi(str);
  if (errno != 0) {
    return -1;
  }
  *result = val;
  return 0;
}
