/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:25:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/09/27 10:25:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

void *ft_memcpy(void *dest, const void *src, size_t n) {
  size_t index = 0;
  uint8_t *dest_char_ptr = (uint8_t *)dest;
  const uint8_t *src_char_ptr = (const uint8_t *)src;

  while (index < n) {
    dest_char_ptr[index] = src_char_ptr[index];
    index++;
  }
  return (dest_char_ptr);
}

void *ft_memset(void *s, int c, size_t n) {
  size_t index = 0;
  uint8_t *s_char_ptr = (uint8_t *)s;

  while (index < n) {
    s_char_ptr[index] = (uint8_t)c;
    index++;
  }
  return (s_char_ptr);
}