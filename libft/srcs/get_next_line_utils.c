/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:19:22 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strjoin(char *s1, char const *s2)
{
	char	*res;
	char	*tmp;
	size_t	len1;
	size_t	len2;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		len1 = 0;
	else
		len1 = gnl_strlen(s1);
	len2 = gnl_strlen(s2);
	res = (char *)malloc(len1 + len2 + 1);
	if (res == NULL)
		return (NULL);
	tmp = res;
	while (len1 != 0 && len1-- != 0)
		*tmp++ = *s1++;
	while (len2 != 0 && len2-- != 0)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (res);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_str_endl(char *s)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	str = s;
	while (*str)
	{
		if (*str == '\n')
			return (str);
		str++;
	}
	return (NULL);
}

char	*gnl_strdup(const char *str)
{
	char	*src;
	size_t	len;
	char	*dst;
	char	*strcp;

	len = gnl_strlen(str);
	src = (char *)str;
	dst = (char *)malloc(len + 1);
	if (NULL == dst)
		return (NULL);
	strcp = dst;
	while (len-- != 0)
		*strcp++ = *src++;
	*strcp = '\0';
	return (dst);
}
