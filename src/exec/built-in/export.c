/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 03:47:21 by vlad              #+#    #+#             */
/*   Updated: 2026/04/27 14:20:32 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_existing_key(t_env_node *head, char *key, char *value)
{
	t_env_node	*current;

	current = head;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			free(current->value);
			current->value = value;
			free(key);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

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

void	ft_hash_table_insert(t_hash_table *hash_map, char *key, char *value)
{
	unsigned long	hash;
	int				index;
	t_env_node		*new;
	t_env_node		*current;

	hash = ft_hash_djb2((unsigned char *)key);
	index = hash % HASH_SIZE;
	if (hash_map->items[index]
		&& ft_update_existing_key(hash_map->items[index], key, value))
		return ;
	new = malloc(sizeof(t_env_node) * 1);
	if (!new)
		return ;
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (!hash_map->items[index])
		hash_map->items[index] = new;
	else
	{
		current = hash_map->items[index];
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

static void	ft_export_single(t_hash_table *hash_map, char *arg)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return ;
	key = ft_strndup(arg, eq - arg);
	if (!ft_is_valid_key(key))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		g_exit_status = 1;
		free(key);
		return ;
	}
	value = ft_strdup(eq + 1);
	ft_hash_table_insert(hash_map, key, value);
}

void	ft_export(t_hash_table *hash_map, char **args)
{
	int	i;

	if (!args[1])
	{
		ft_env(hash_map);
		return ;
	}
	i = 1;
	while (args[i])
	{
		ft_export_single(hash_map, args[i]);
		i++;
	}
}
