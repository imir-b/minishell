/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemini <gemini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by gemini            #+#    #+#             */
/*   Updated: 2026/04/29 12:00:00 by gemini           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_open_file(t_ast *node)
{
	int	fd;

	fd = -1;
	if (node->type == NODE_REDIR_IN)
		fd = open(node->redir_data->file, O_RDONLY);
	else if (node->type == NODE_REDIR_OUT)
		fd = open(node->redir_data->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->type == NODE_APPEND)
		fd = open(node->redir_data->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (node->type == NODE_HEREDOC)
		fd = open(node->redir_data->file, O_RDONLY); // Heredoc is pre-processed into a file
	if (fd == -1)
		perror(node->redir_data->file);
	return (fd);
}

/**
 * ft_exec_redir - Handles file redirections (<, >, >>, <<).
 * Backups standard FDs, applies all redirections in the chain,
 * and restores FDs after execution.
 */
int	ft_exec_redir(t_ast *node, t_minishell *data)
{
	int	fd;
	int	stdin_backup;
	int	stdout_backup;
	int	status;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	status = 0;
	while (node && node->type >= NODE_REDIR_IN && node->type <= NODE_HEREDOC)
	{
		fd = ft_open_file(node);
		if (fd == -1)
		{
			g_exit_status = 1;
			status = 1;
			break ;
		}
		if (node->type == NODE_REDIR_IN || node->type == NODE_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		if (node->left && node->left->type >= NODE_REDIR_IN
			&& node->left->type <= NODE_HEREDOC)
			node = node->left;
		else
			break ;
	}
	if (status == 0)
		status = ft_exec_node(node->left, data);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	return (status);
}
