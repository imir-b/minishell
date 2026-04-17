/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:05:34 by username          #+#    #+#             */
/*   Updated: 2026/04/16 02:39:51 by vlad             ###   ########.fr       */
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

int	ft_process_dollar(char *arg, int *i, t_hash_table *hash_map)
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
		{
			if (!quotes && (arg[i + 1] == '\'' || arg[i + 1] == '\"'))
				i++;
			else
				len += ft_process_dollar(arg, &i, hash_map);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	ft_write_var(char *key, char *ret, int *j, t_hash_table *map)
{
	char		*st;
	t_env_node	*var;
	int			k;
	int			idx;

	if (ft_strcmp(key, "?") == 0)
	{
		st = ft_itoa(g_exit_status);
		k = 0;
		while (st && st[k])
			ret[(*j)++] = st[k++];
		free(st);
		return ;
	}
	idx = ft_hash_djb2((unsigned char *)key) % HASH_SIZE;
	var = map->items[idx];
	while (var && ft_strcmp(var->key, key) != 0)
		var = var->next;
	k = 0;
	while (var && var->value && var->value[k])
		ret[(*j)++] = var->value[k++];
}

int	ft_handle_dollar(char *str, char *ret, int *j, t_hash_table *map)
{
	char	*key;
	int		i_adv;

	i_adv = 1;
	key = ft_extract_key(&str[1]);
	if (!key)
	{
		ret[(*j)++] = '$';
		return (i_adv);
	}
	i_adv += ft_strlen(key);
	ft_write_var(key, ret, j, map);
	free(key);
	return (i_adv);
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
		{
			if (!quotes && (arg[i + 1] == '\'' || arg[i + 1] == '\"'))
				i++;
			else	
				i +=ft_handle_dollar(&arg[i], ret, &j, hash_map);
		}
		else
			ret[j++] = arg[i++];
	}
	ret[j] = '\0';
	return (ret);
}
