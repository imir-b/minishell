/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 10:00:00 by gemini            #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int	ft_is_assignment(char *arg)
{
	char	*eq;
	char	*key;
	int		res;

	if (!arg)
		return (0);
	eq = ft_strchr(arg, '=');
	if (!eq || eq == arg)
		return (0);
	key = ft_strndup(arg, eq - arg);
	res = ft_is_valid_key(key);
	free(key);
	return (res);
}

int	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	ft_exec_builtin(t_ast *node, t_minishell *data)
{
	char	*cmd;
	char	**args;

	g_exit_status = 0;
	cmd = node->cmd_data->cmd;
	args = node->cmd_data->args;
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(args);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(data->hash_map, args[1]);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(data->hash_map, args);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(data->hash_map, args[1]);
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(data->hash_map);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(data, args);
	return (g_exit_status);
}

int	ft_handle_exec_error(char *cmd, char *path)
{
	struct stat	path_stat;

	if (!path || (ft_strchr(cmd, '/') && access(cmd, F_OK) != 0))
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (g_exit_status = 127);
	}
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		return (g_exit_status = 126);
	}
	if (access(path, X_OK) != 0)
	{
		perror(cmd);
		return (g_exit_status = 126);
	}
	return (0);
}

void	ft_apply_assignments(t_hash_table *h_m, char **args, int count, int exp)
{
	int		i;
	char	*eq;
	char	*key;
	char	*val;

	i = 0;
	while (i < count)
	{
		eq = ft_strchr(args[i], '=');
		key = ft_strndup(args[i], eq - args[i]);
		val = ft_strdup(eq + 1);
		ft_hash_table_insert(h_m, key, val, exp);
		i++;
	}
}
