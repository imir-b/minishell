/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:24:35 by vbleskin          #+#    #+#             */
/*   Updated: 2026/05/08 01:58:51 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	*ft_free_all(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

static size_t	ft_wordlen(const char *start, char sep)
{
	size_t	len;

	len = 0;
	while (*(start + len) && *(start + len) != sep)
		len++;
	return (len);
}

static int	ft_countwords(const char *str, char sep)
{
	int		count;
	size_t	len;

	count = 0;
	while (*str)
	{
		if (*str != sep)
		{
			len = ft_wordlen(str, sep);
			str += len;
			count++;
		}
		else
			str++;
	}
	return (count);
}

static char	**ft_fill_array(char **dest, const char *str, char sep)
{
	int		word;
	size_t	len;

	word = 0;
	while (*str)
	{
		if (*str != sep)
		{
			len = ft_wordlen(str, sep);
			dest[word] = malloc(sizeof(char) * (len + 1));
			if (!dest[word])
				return (ft_free_all(dest));
			ft_strlcpy(dest[word++], str, len + 1);
			str += len;
		}
		else
			str++;
	}
	dest[word] = NULL;
	return (dest);
}

char	**ft_split(const char *str, char sep)
{
	char	**dest;

	if (!str)
		return (NULL);
	dest = malloc(sizeof(char *) * (ft_countwords(str, sep) + 1));
	if (!dest)
		return (NULL);
	return (ft_fill_array(dest, str, sep));
}
