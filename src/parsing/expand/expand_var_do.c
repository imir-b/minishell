/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_do.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:05:34 by vbleskin          #+#    #+#             */
/*   Updated: 2026/05/08 01:15:33 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_write_var(char *key, char *ret, int *j, t_hash_table *map)
{
	char		*st;
	t_env_node	*var;
	int			k;

	if (ft_strcmp(key, "?") == 0)
	{
		st = ft_itoa(g_exit_status);
		k = 0;
		while (st && st[k])
			ret[(*j)++] = st[k++];
		free(st);
		return ;
	}
	var = ft_find_env_node(map, key);
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

static void	ft_handle_quotes_exp(char *arg, int *i, char *ret, int *vars)
{
	int	*j;
	int	*q;

	j = &vars[0];
	q = &vars[1];
	*q ^= arg[*i];
	if (arg[*i] == '\'')
		ret[(*j)++] = '\x01';
	else
		ret[(*j)++] = '\x02';
	(*i)++;
}

static void	ft_handle_dollar_in_arg(char *arg, int *i, char *ret, void **data)
{
	int				*j;
	t_hash_table	*map;

	j = (int *)data[0];
	map = (t_hash_table *)data[1];
	if (!arg[*i + 1] || (arg[*i + 1] != '\'' && arg[*i + 1] != '\"'))
		*i += ft_handle_dollar(&arg[*i], ret, j, map);
	else
		(*i)++;
}

char	*ft_expand_single_arg(char *arg, t_hash_table *hash_map)
{
	int		i;
	int		vars[2];
	void	*data[2];
	char	*ret;

	vars[0] = ((vars[1] = (i = 0)));
	ret = malloc(sizeof(char) * (ft_expanded_len(arg, hash_map) + 1));
	if (!ret)
		return (NULL);
	while (arg[i])
	{
		if ((arg[i] == '\'' || arg[i] == '\"')
			&& (!vars[1] || vars[1] == arg[i]))
			ft_handle_quotes_exp(arg, &i, ret, vars);
		else if (arg[i] == '$' && vars[1] != '\'')
		{
			data[0] = &vars[0];
			data[1] = hash_map;
			ft_handle_dollar_in_arg(arg, &i, ret, data);
		}
		else
			ret[vars[0]++] = arg[i++];
	}
	return (ret[vars[0]] = '\0', ret);
}
