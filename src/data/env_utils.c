/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:00:00 by gemini            #+#    #+#             */
/*   Updated: 2026/05/07 11:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_valid_key(char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_key_len(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (str[0] == '?' || (str[0] >= '0' && str[0] <= '9'))
		return (1);
	i = 0;
	if (!str[i] || (!(str[i] >= 'a' && str[i] <= 'z')
			&& !(str[i] >= 'A' && str[i] <= 'Z') && str[i] != '_'))
		return (0);
	i++;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
		i++;
	return (i);
}

char	*ft_extract_key(char *str)
{
	char	*key;
	int		len;
	int		i;

	len = ft_key_len(str);
	if (len == 0)
		return (NULL);
	key = malloc(sizeof(char) * (len + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (i < len)
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

void	ft_update_shlvl(t_hash_table *hash_map)
{
	t_env_node	*current;
	int			index;
	int			shlvl;

	shlvl = 1;
	index = ft_hash_djb2((unsigned char *)"SHLVL") % HASH_SIZE;
	current = hash_map->items[index];
	while (current)
	{
		if (!ft_strcmp(current->key, "SHLVL"))
		{
			shlvl += ft_atoi(current->value);
			break ;
		}
		current = current->next;
	}
	ft_hash_table_insert(hash_map, ft_strdup("SHLVL"), ft_itoa(shlvl), 1);
}

void	ft_set_default_env(t_hash_table *hash_map)
{
	char	buf[PATH_MAX];

	if (!ft_get_value(hash_map, "PWD"))
	{
		if (getcwd(buf, PATH_MAX))
			ft_hash_table_insert(hash_map, ft_strdup("PWD"), ft_strdup(buf), 1);
	}
}
