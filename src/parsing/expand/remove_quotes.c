/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:50:47 by vbleskin          #+#    #+#             */
/*   Updated: 2026/04/10 18:31:22 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_quotes(char *arg)
{
	int		i;
	int		j;
	int		quote;
	char	*dest;

	dest = malloc(sizeof(char) * (ft_strlen(arg) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (arg[i])
	{
		if ((arg[i] == '\'' || arg[i] == '\"') && (!quote || quote == arg[i]))
			quote ^= arg[i++];
		else
			dest[j++] = arg[i++];
	}
	dest[j] = '\0';
	return (dest);
}

char	**ft_remove_quotes_array(char **args)
{
	int		i;
	int		len;
	char	**dest;

	len = 0;
	while (args[len])
		len++;
	dest = malloc(sizeof(char *) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (args[i])
	{
		dest[i] = ft_remove_quotes(args[i]);
		if (!dest[i])
			return (ft_free_tab(dest), NULL);
		i++;
	}
	dest[i] = NULL;
	ft_free_tab(args);
	return (dest);
}
