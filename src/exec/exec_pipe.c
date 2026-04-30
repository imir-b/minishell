/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemini <gemini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by gemini            #+#    #+#             */
/*   Updated: 2026/04/29 12:00:00 by gemini           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ft_exec_pipe - Implements the pipeline execution.
 * Creates a pipe and forks two children. The left child's stdout is 
 * connected to the pipe's write end, and the right child's stdin 
 * is connected to the pipe's read end.
 */
int	ft_exec_pipe(t_ast *node, t_minishell *data)
{
	int		pipe_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	pid_left = fork();
	if (pid_left == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exit(ft_exec_node(node->left, data));
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		exit(ft_exec_node(node->right, data));
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (g_exit_status);
}
