/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 22:09:49 by vlad              #+#    #+#             */
/*   Updated: 2026/04/15 23:57:58 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc_len(char *line, t_hash_table *hash_map)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$')
			len += ft_process_dollar(line, &i, hash_map);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*ft_expand_heredoc_line(char *line, t_hash_table *hash_map)
{
	int		i;
	int		j;
	char	*expanded_line;

	if (!line)
		return (NULL);
	expanded_line = malloc(sizeof(char) * (ft_heredoc_len(line, hash_map) + 1));
	if (!expanded_line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$')
			i +=ft_handle_dollar(&line[i], expanded_line, &j, hash_map);
		else
			expanded_line[j++] = line[i++];
	}
	expanded_line[j] = '\0';
	return (expanded_line);
}
