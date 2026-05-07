/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:16:22 by vlad              #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_external(t_ast *node, t_minishell *data, int i, char **orig_args)
{
	pid_t	pid;
	int		status;
	char	**env_tab;

	node->cmd_data->path = ft_get_cmd_path(node->cmd_data->cmd, data->hash_map);
	if (ft_handle_exec_error(node->cmd_data->cmd, node->cmd_data->path))
		return (g_exit_status);
	pid = fork();
	if (pid == 0)
	{
		ft_apply_assignments(data->hash_map, orig_args, i, 1);
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

int	ft_exec_command(t_ast *node, t_minishell *data)
{
	int		i;
	char	**original_args;
	char	*original_cmd;
	int		res;

	i = 0;
	while (node->cmd_data->args[i] && ft_is_assignment(node->cmd_data->args[i]))
		i++;
	if (!node->cmd_data->args[i])
	{
		ft_apply_assignments(data->hash_map, node->cmd_data->args, i, 0);
		return (g_exit_status = 0);
	}
	original_args = node->cmd_data->args;
	original_cmd = node->cmd_data->cmd;
	node->cmd_data->args = &original_args[i];
	node->cmd_data->cmd = node->cmd_data->args[0];
	if (ft_is_builtin(node->cmd_data->cmd))
		res = ft_exec_builtin(node, data);
	else
		res = ft_exec_external(node, data, i, original_args);
	node->cmd_data->args = original_args;
	node->cmd_data->cmd = original_cmd;
	return (res);
}

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
