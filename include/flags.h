/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:13:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/08/27 22:13:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H

#include <stdbool.h>
#include <stdint.h>

#define DEFAULT_FIRST_HOP 1
#define DEFAULT_MAX_HOPS 64
#define DEFAULT_PORT 33434
#define DEFAULT_TRIES 3
#define DEFAULT_WAIT 3

typedef struct {
    char *hostname;
    uint8_t first_hop_value;
    uint8_t max_hops_value;
    uint16_t port_value;
    uint8_t tries_value;
    uint8_t wait_value;
    struct {
      uint8_t first_hop: 1;
      uint8_t max_hops: 1;
      uint8_t port: 1;
      uint8_t tries: 1;
      uint8_t wait: 1;
      uint8_t _reserved: 3;
    } options;
} flags_t;

int8_t parse_flags(int argc, char *argv[], flags_t *flags);

#endif