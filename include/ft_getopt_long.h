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

#define ft_no_argument 0
#define ft_required_argument 1
#define ft_optional_argument 2

extern int ft_optind;
extern char *ft_optarg;

struct ft_option {
    const char *name;
    int has_arg;
    int *flag;
    int val;
};

int ft_getopt_long(int argc, char *argv[], const char *optstring, const struct ft_option *longopts, int *longindex);

#endif