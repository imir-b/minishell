/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:44:19 by vlad              #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_fill_redir(t_node_type type, char *file, int flags, t_ast *node)
{
	node->type = type;
	node->redir_data->file = ft_strdup(file);
	node->redir_data->flags = flags;
}

static void	ft_handle_heredoc_quotes(t_token *file_name, t_ast *node)
{
	char	*clean_delim;

	node->redir_data->expand_heredoc = 1;
	if (ft_strchr(file_name->value, '\'') || ft_strchr(file_name->value, '\"'))
	{
		node->redir_data->expand_heredoc = 0;
		clean_delim = ft_remove_quotes(file_name->value);
		free(file_name->value);
		file_name->value = clean_delim;
	}
	ft_fill_redir(NODE_HEREDOC, file_name->value,
		O_RDONLY | O_CREAT | O_TRUNC, node);
}

static void	ft_assign_redir_type(t_token *current, t_token *file, t_ast *node)
{
	node->redir_data->expand_heredoc = 0;
	if (current->type == TOK_REDIR_IN)
		ft_fill_redir(NODE_REDIR_IN, file->value, O_RDONLY, node);
	else if (current->type == TOK_REDIR_OUT)
		ft_fill_redir(NODE_REDIR_OUT, file->value,
			O_WRONLY | O_CREAT | O_TRUNC, node);
	else if (current->type == TOK_APPEND)
		ft_fill_redir(NODE_APPEND, file->value,
			O_WRONLY | O_CREAT | O_APPEND, node);
	else if (current->type == TOK_HEREDOC)
		ft_handle_heredoc_quotes(file, node);
}

static t_ast	*ft_alloc_redir_node(void)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast) * 1);
	if (!node)
		return (NULL);
	node->cmd_data = NULL;
	node->redir_data = malloc(sizeof(t_redir_data) * 1);
	if (!node->redir_data)
		return (free(node), NULL);
	node->right = NULL;
	return (node);
}

t_ast	*ft_create_redir_node(t_token *curr, t_token *first, t_minishell *data)
{
	t_ast	*node;
	t_token	*file;
	t_token	*next;

	file = curr->next;
	if (!file)
		return (NULL);
	if (curr == first && (first = ft_extract_redir_tokens(curr, file, first))
		&& first->type == TOK_L_PAREN)
		return (ft_syntax_error("("), NULL);
	else if (curr != first)
		first = ft_extract_redir_tokens(curr, file, first);
	node = ft_alloc_redir_node();
	if (!node)
		return (NULL);
	ft_assign_redir_type(curr, file, node);
	(free(curr->value), free(curr), free(file->value), free(file));
	next = ft_find_operator(first, TOK_REDIR_IN, TOK_HEREDOC);
	if (next)
		node->left = ft_create_redir_node(next, first, data);
	else
		node->left = ft_create_tree(first, data);
	return (node);
}
