/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:05:34 by username          #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_process_dollar(char *arg, int *i, t_hash_table *hash_map)
{
	char		*key;
	char		*status_str;
	t_env_node	*var;
	int			len;

	key = ft_extract_key(&(arg[++(*i)]));
	if (!key)
		return (1);
	*i += ft_strlen(key);
	len = 0;
	if (ft_strcmp(key, "?") == 0)
	{
		status_str = ft_itoa(g_exit_status);
		len = ft_strlen(status_str);
		free(status_str);
	}
	else
	{
		var = ft_find_env_node(hash_map, key);
		if (var && var->value)
			len = ft_strlen(var->value);
	}
	free(key);
	return (len);
}

static void	ft_process_char_len(char *arg, int *i, int *len,
	int *quotes, t_hash_table *hash_map)
{
	if ((arg[*i] == '\'' || arg[*i] == '\"') && (!*quotes || *quotes == arg[*i]))
	{
		*quotes ^= arg[*i];
		(*len)++;
		(*i)++;
	}
	else if (arg[*i] == '$' && *quotes != '\'')
	{
		if (!*quotes && (arg[*i + 1] == '\'' || arg[*i + 1] == '\"'))
			(*i)++;
		else
			*len += ft_process_dollar(arg, i, hash_map);
	}
	else
	{
		(*len)++;
		(*i)++;
	}
}

int	ft_expanded_len(char *arg, t_hash_table *hash_map)
{
	int	i;
	int	quotes;
	int	len;

	i = 0;
	quotes = 0;
	len = 0;
	while (arg[i])
		ft_process_char_len(arg, &i, &len, &quotes, hash_map);
	return (len);
}
