/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_super_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:10:23 by vlad              #+#    #+#             */
/*   Updated: 2026/03/20 01:11:39 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_super_join(char const *s1, char const *s2, char sep)
{
	char	*str;
	int		size;
	int		i;
	int		j;

	str = NULL;
	size = sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2);
	str = malloc(size);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = sep;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = ('\0');
	return (str);
}
