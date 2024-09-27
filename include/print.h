/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:13:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/08/18 14:13:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

#include <netinet/ip_icmp.h>

#include "flags.h"
#include "traceroute.h"

void print_traceroute_start(const traceroute_t *traceroute);
void print_traceroute_result(const traceroute_result_t *result, bool is_first_try, struct sockaddr_in previous);

void print_help(const char *binary_name);
void print_usage(const char *binary_name);

#endif