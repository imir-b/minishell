/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:05:34 by username          #+#    #+#             */
/*   Updated: 2026/04/10 21:56:05 by vlad             ###   ########.fr       */
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

static int	ft_process_dollar(char *arg, int *i, t_hash_table *hash_map)
{
	char		*key;
	char		*status_str;
	t_env_node	*var_data;
	int			len;

	len = 0;
	key = ft_extract_key(&(arg[++(*i)]));
	if (key)
	{
		*i += ft_strlen(key);
		if (strcmp(key, "?") == 0)
		{
			status_str = ft_itoa(g_exit_status);
			len += ft_strlen(status_str);
			free (status_str);
		}
		else
		{
			var_data = ft_expand_variable(key, hash_map);
			if (var_data && var_data->value)
				len += ft_strlen(var_data->value);
			}
		free(key);
	}
	else
		len++;
	return (len);
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
	{
		if ((arg[i] == '\'' || arg[i] == '\"') && (!quotes || quotes == arg[i]))
		{
			quotes ^= arg[i];
			len++;
			i++;
		}
		else if (arg[i] == '$' && quotes != '\'')
			len += ft_process_dollar(arg, &i, hash_map);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

/**fonction de merde a decouper !! */
static void	ft_handle_dollar(char *arg, char *ret, int *i, int *j,
	t_hash_table	*map)
{
	char		*key;
	char		*status_str;
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
	if (strcmp(key, "?") == 0)
	{
		status_str = ft_itoa(g_exit_status);
		k = 0;
		while (status_str[k])
			ret[(*j)++] = status_str[k++];
		free(status_str);
	}
	else
	{
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
	}
	free(key);
}

char	*ft_expand_single_arg(char *arg, t_hash_table *hash_map)
{
	int		i;
	int		j;
	int		quotes;
	char	*ret;

	quotes = ((i = ((j = 0))));
	ret = malloc(sizeof(char) * (ft_expanded_len(arg, hash_map) + 1));
	if (!ret)
		return (NULL);
	while (arg[i])
	{
		if ((arg[i] == '\'' || arg[i] == '\"') && (!quotes || quotes == arg[i]))
		{
			quotes ^= arg[i];
			ret[j++] = arg[i++];
		}
		else if (arg[i] == '$' && quotes != '\'')
			ft_handle_dollar(arg, ret, &i, &j, hash_map);
		else
			ret[j++] = arg[i++];
	}
	ret[j] = '\0';
	return (ret);
}
