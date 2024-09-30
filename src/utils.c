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

#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

static size_t count_white_spaces(const char *s);
static int check_overflow(const char *str, size_t index, long result, int sign);

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

char *ft_strchr(const char *s, int32_t c) {
  size_t index;

  index = 0;
  while (s[index] != '\0') {
    if (s[index] == (char)c)
      return ((char *)s + index);
    index++;
  }
  if (s[index] == c)
    return ((char *)s + index);
  return (NULL);
}

int32_t ft_strcmp(const char *s1, const char *s2) {
  while (*s1 != '\0' && *s2 != '\0') {
    if (*s1 != *s2)
      return (*s1 - *s2);
    s1++;
    s2++;
  }
  return (*s1 - *s2);
}

int ft_isdigit(int c) { return (c >= '0' && c <= '9'); }

int ft_atoi(const char *str) {
  long result;
  int overflow;
  int sign;
  size_t index;

  result = 0;
  sign = 1;
  str += count_white_spaces(str);
  index = 0;
  if (str[index] == '-') {
    sign = -1;
    str++;
  } else if (str[index] == '+')
    str++;
  while (ft_isdigit(str[index])) {
    overflow = check_overflow(str, index, result, sign);
    if (overflow)
      return (overflow);
    result = result * 10 + (str[index] - '0');
    index++;
  }
  return ((int)result * sign);
}

static size_t count_white_spaces(const char *s) {
  size_t index;

  index = 0;
  while (s[index] == ' ' || s[index] == '\f' || s[index] == '\n' || s[index] == '\r' ||
         s[index] == '\t' || s[index] == '\v')
    index++;
  return (index);
}

static int check_overflow(const char *str, size_t index, long result, int sign) {
  if (INT_MAX / 10 < result * sign || INT_MAX - (str[index] - '0') < result * 10 * sign) {
    errno = EOVERFLOW;
    return ((int)INT_MAX);
  }
  if (INT_MIN / 10 > result * sign || INT_MIN + (str[index] - '0') > result * 10 * sign) {
    errno = EOVERFLOW;
    return ((int)INT_MIN);
  }
  return (0);
}