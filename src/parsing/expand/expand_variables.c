/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:05:34 by username          #+#    #+#             */
/*   Updated: 2026/04/09 16:54:42 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_node	*ft_expand_variable(char *cursor, t_hash_table *h_map)
{
	t_env_node	*current;
	char		*key;
	int			index;

	key = ft_extract_key(cursor);
	index = ft_hash_djb2((unsigned char *) key) % HASH_SIZE;
	if (!h_map->items[index])
		return (free(key), NULL);
	current = h_map->items[index];
	while (current && ft_strcmp(current->key, key) != 0)
		current = current->next;
	free(key);
	if (current)
		return (current);
	return (NULL);
}

int	ft_expanded_len(char *arg, t_hash_table *hash_map)
{
	int			i;
	int			single_quote;
	int			len;
	char		*key;
	t_env_node	*var_data;

	i = ((single_quote = ((len = 0))));
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			single_quote = !single_quote;
			len++;
			i++;
		}
		else if (arg[i] == '$' && !single_quote)
		{
			key = ft_extract_key(&(arg[++i]));
			if (key)
			{
				i += ft_strlen(key);
				var_data = ft_expand_variable(key, hash_map);
				if (var_data && var_data->value)
					len += ft_strlen(var_data->value);
				free(key);
			}
			else
				len++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void ft_handle_dollar(char * arg, char * ret, int * i, int * j,
	t_hash_table	*map)
{
	char		*key;
	t_env_node	*var_data;
	int			k;
	int			index;

	(*i)++;
	key = ft_extract_key(&(arg[*i]));
	if (!key)
	{
		ret[(*j)++] = '$';
		return ;
	}
	(*i) += ft_strlen(key);
	index = ft_hash_djb2((unsigned char *) key) % HASH_SIZE;
	var_data = map->items[index];
	while (var_data && ft_strcmp(var_data->key, key) != 0)
		var_data = var_data->next;
	if (var_data && var_data->value)
	{
		k = 0;
		while (var_data->value[k])
			ret[(*j)++] = var_data->value[k++];
	}
	free(key);
}

char	*ft_expand_single_arg(char *arg, t_hash_table *hash_map)
{
	int		i;
	int		j;
	int		single_quote;
	char	*ret;

	single_quote = ((i = ((j = 0))));
	ret = malloc(sizeof(char) * (ft_expanded_len(arg, hash_map) + 1));
	if (!ret)
		return (NULL);
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			single_quote = !single_quote;
			ret[j++] = arg[i++];
		}
		else if (arg[i] == '$' && !single_quote)
			ft_handle_dollar(arg, ret, &i, &j, hash_map);
		else
			ret[j++] = arg[i++];
	}
	ret[j] = '\0';
	return (ret);
}
