/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 03:47:21 by vlad              #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_export_single(t_hash_table *hash_map, char *arg)
{
	char		*eq;
	char		*key;
	char		*value;
	t_env_node	*node;

	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		node = ft_find_env_node(hash_map, arg);
		if (ft_is_valid_key(arg) && node)
			node->is_exported = 1;
		else if (!ft_is_valid_key(arg))
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
		return (g_exit_status = 1, (void)free(key));
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

static void	ft_print_export_node(char *env_line)
{
	char	*eq;

	printf("declare -x ");
	eq = ft_strchr(env_line, '=');
	if (eq)
	{
		*eq = '\0';
		printf("%s=\"%s\"\n", env_line, eq + 1);
	}
	else
		printf("%s\n", env_line);
}

static void	ft_print_export(t_hash_table *hash_map)
{
	char	**env;
	int		i;

	env = ft_get_env_tab(hash_map);
	if (!env)
		return ;
	ft_sort_env(env);
	i = 0;
	while (env[i])
	{
		ft_print_export_node(env[i]);
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
