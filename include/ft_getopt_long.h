/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt_long.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:34:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/09/27 11:34:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETOPT_LONG_H
#define FT_GETOPT_LONG_H

#include <getopt.h>

int ft_getopt_long(int argc, char *const argv[], const char *optstring, const struct option *longopts, int *longindex);

#endif