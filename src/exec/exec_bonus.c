/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemini <gemini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by gemini            #+#    #+#             */
/*   Updated: 2026/04/29 17:50:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
	* ft_exec_logical - Implements && and || logic.
	* Respects Bash behavior: && executes right if left succeeds,
	* || executes right if left fails.
	*/
int	ft_exec_logical(t_ast *node, t_minishell *data)
{
	int	status;

	status = ft_exec_node(node->left, data);
	if (node->type == NODE_AND)
	{
		if (status == 0)
			return (ft_exec_node(node->right, data));
	}
	else if (node->type == NODE_OR)
	{
		if (status != 0)
			return (ft_exec_node(node->right, data));
	}
	return (status);
}

/**
	* ft_exec_subshell - Executes a command tree inside a forked process.
	* Used for ( ) parentheses to isolate execution environment.
	*/
int	ft_exec_subshell(t_ast *node, t_minishell *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		exit(ft_exec_node(node->left, data));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (g_exit_status);
}
