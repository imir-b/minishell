/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemini <gemini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by gemini            #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
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
		fd = open(node->redir_data->file, O_RDONLY);
	if (fd == -1)
		perror(node->redir_data->file);
	return (fd);
}

static int	ft_apply_all_redirs(t_ast **node, t_hash_table *map)
{
	int	fd;

	while (*node && (*node)->type >= NODE_REDIR_IN
		&& (*node)->type <= NODE_HEREDOC)
	{
		/* Fix: Expand each redirection in the chain before applying it.
		   This ensures $VARS are handled for all redirections. */
		if (ft_expand_node(*node, map))
			return (1);
		fd = ft_open_file(*node);
		if (fd == -1)
			return (g_exit_status = 1, 1);
		if ((*node)->type == NODE_REDIR_IN || (*node)->type == NODE_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		if ((*node)->left && (*node)->left->type >= NODE_REDIR_IN
			&& (*node)->left->type <= NODE_HEREDOC)
			*node = (*node)->left;
		else
			break ;
	}
	return (0);
}

/**
	* ft_exec_redir - Handles file redirections (<, >, >>, <<).
	* Backups standard FDs, applies all redirections in the chain,
	* and restores FDs after execution.
	*/
int	ft_exec_redir(t_ast *node, t_minishell *data)
{
	int	stdin_backup;
	int	stdout_backup;
	int	status;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (ft_apply_all_redirs(&node, data->hash_map) == 0)
		status = ft_exec_node(node->left, data);
	else
		status = 1;
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	return (status);
}
