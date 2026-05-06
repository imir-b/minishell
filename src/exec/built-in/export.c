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

int	ft_update_existing_key(t_env_node *head, char *key, char *value, int export_flag)
{
	t_env_node	*current;

	current = head;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			free(current->value);
			current->value = value;
			if (export_flag)
				current->is_exported = 1;
			free(key);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	ft_hash_table_insert(t_hash_table *hash_map, char *key, char *value, int export_flag)
{
	unsigned long	hash;
	int				index;
	t_env_node		*new;
	t_env_node		*current;

	hash = ft_hash_djb2((unsigned char *)key);
	index = hash % HASH_SIZE;
	if (hash_map->items[index]
		&& ft_update_existing_key(hash_map->items[index], key, value, export_flag))
		return ;
	new = malloc(sizeof(t_env_node) * 1);
	if (!new)
		return ;
	new->key = key;
	new->value = value;
	new->is_exported = export_flag;
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
	char		*eq;
	char		*key;
	char		*value;
	t_env_node	*node;

	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		if (ft_is_valid_key(arg))
		{
			node = ft_find_env_node(hash_map, arg);
			if (node)
				node->is_exported = 1;
		}
		else
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			g_exit_status = 1;
		}
		return ;
	}
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
	ft_hash_table_insert(hash_map, key, value, 1);
}

static void	ft_sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	ft_print_export(t_hash_table *hash_map)
{
	char	**env;
	int		i;
	char	*eq;

	env = ft_get_env_tab(hash_map);
	if (!env)
		return ;
	ft_sort_env(env);
	i = 0;
	while (env[i])
	{
		printf("declare -x ");
		eq = ft_strchr(env[i], '=');
		if (eq)
		{
			*eq = '\0';
			printf("%s=\"%s\"\n", env[i], eq + 1);
		}
		else
			printf("%s\n", env[i]);
		i++;
	}
	ft_free_tab(env);
}

void	ft_export(t_hash_table *hash_map, char **args)
{
	int	i;

	if (!args[1])
	{
		ft_print_export(hash_map);
		return ;
	}
	i = 1;
	while (args[i])
	{
		ft_export_single(hash_map, args[i]);
		i++;
	}
}
