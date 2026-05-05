/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:16:22 by vlad              #+#    #+#             */
/*   Updated: 2026/04/29 17:50:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <sys/stat.h>

/**
 * ft_is_builtin - Checks if a command is a shell built-in.
 */
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

/**
 * ft_exec_builtin - Dispatches execution to the corresponding built-in function.
 * Note: These are executed in the current process if not piped.
 */
int	ft_exec_builtin(t_ast *node, t_minishell *data)
{
	char	*cmd;
	char	**args;

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

static int	ft_handle_exec_error(char *cmd, char *path)
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

/**
 * ft_exec_command - Handles execution of simple commands.
 * Resolves path, forks, and executes using execve.
 */
int	ft_exec_command(t_ast *node, t_minishell *data)
{
	pid_t	pid;
	int		status;
	char	**env_tab;
	int		err;

	if (!node->cmd_data->cmd || !*node->cmd_data->cmd)
		return (0);
	if (ft_is_builtin(node->cmd_data->cmd))
		return (ft_exec_builtin(node, data));
	node->cmd_data->path = ft_get_cmd_path(node->cmd_data->cmd, data->hash_map);
	err = ft_handle_exec_error(node->cmd_data->cmd, node->cmd_data->path);
	if (err)
		return (err);
	pid = fork();
	if (pid == 0)
	{
		env_tab = ft_get_env_tab(data->hash_map);
		execve(node->cmd_data->path, node->cmd_data->args, env_tab);
		perror("execve");
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (g_exit_status);
}

/**
 * ft_exec_node - Main recursive entry point for AST execution.
 * Routes nodes to their specific handlers based on type.
 */
int	ft_exec_node(t_ast *node, t_minishell *data)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
	{
		ft_expand_node(node, data->hash_map);
		return (ft_exec_command(node, data));
	}
	if (node->type == NODE_PIPE)
		return (ft_exec_pipe(node, data));
	if (node->type >= NODE_REDIR_IN && node->type <= NODE_HEREDOC)
	{
		if (ft_expand_node(node, data->hash_map))
			return (1);
		return (ft_exec_redir(node, data));
	}
	if (node->type == NODE_AND || node->type == NODE_OR)
		return (ft_exec_logical(node, data));
	if (node->type == NODE_SUBSHELL)
		return (ft_exec_subshell(node, data));
	return (0);
}

void	ft_execute(t_minishell *data)
{
	ft_setup_signals_exec();
	ft_exec_node(data->ast, data);
	ft_setup_signals_interactive();
}
