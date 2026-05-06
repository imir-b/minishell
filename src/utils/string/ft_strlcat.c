/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:33:06 by vbleskin          #+#    #+#             */
/*   Updated: 2026/05/06 13:57:08 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	ft_strlcat(char *dest, const char *src, size_t s)
{
	size_t	i;
	size_t	j;
	size_t	lenlen;

	i = ft_strlen((const char *)dest);
	j = 0;
	if (s > (size_t)i && s > 0)
	{
		lenlen = ft_strlen(src) + i;
		while (src[j] && (i + j) < (s - 1))
		{
			dest[i + j] = src[j];
			j++;
		}
		dest[i + j] = ('\0');
	}
	else
		lenlen = ft_strlen(src) + s;
	return (lenlen);
}
