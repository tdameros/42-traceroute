/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:29:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/09/27 10:29:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

void *ft_memcpy(void *dest, const void *src, size_t n);
void *ft_memset(void *s, int c, size_t n);
char *ft_strchr(const char *s, char c);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_atoi(const char *str);

#endif