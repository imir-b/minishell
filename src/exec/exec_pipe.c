/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemini <gemini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by gemini            #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_child_left(t_ast *node, t_minishell *data, int *pipe_fd)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	exit(ft_exec_node(node->left, data));
}

static void	ft_child_right(t_ast *node, t_minishell *data, int *pipe_fd)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	exit(ft_exec_node(node->right, data));
}

/**
	* ft_exec_pipe - Implements the pipeline execution.
	* Creates a pipe and forks two children. The left child's stdout is 
	* connected to the pipe's write end, and the right child's stdin 
	* is connected to the pipe's read end.
	*/
int	ft_exec_pipe(t_ast *node, t_minishell *data)
{
	int		p_fd[2];
	pid_t	pid_l;
	pid_t	pid_r;
	int		status;

	if (pipe(p_fd) == -1)
		return (perror("pipe"), 1);
	pid_l = fork();
	if (pid_l == 0)
		ft_child_left(node, data, p_fd);
	pid_r = fork();
	if (pid_r == 0)
		ft_child_right(node, data, p_fd);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid_l, NULL, 0);
	waitpid(pid_r, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (g_exit_status);
}
