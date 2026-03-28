/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:44:19 by vlad              #+#    #+#             */
/*   Updated: 2026/03/27 16:16:39 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_fill_redir(t_node_type type, char *file, int flags, t_ast *node)
{
	node->type = type;
	node->redir_data->file = file;
	node->redir_data->flags = flags;
}

t_token	*ft_extract_redir_tokens(t_token *op, t_token *file_name,
			t_token *first)
{
	t_token	*prev_tok;
	t_token	*next_tok;

	prev_tok = op->prev;
	next_tok = file_name->next;
	if (prev_tok)
		prev_tok->next = next_tok;
	if (next_tok)
		next_tok->prev = prev_tok;
	if (op == first)
		return (next_tok);
	return (first);
}

t_ast	*ft_create_redir_node(t_token *current, t_token *first,
			t_minishell *data)
{
	t_ast	*node;
	t_token	*file_name;

	file_name = current->next;
	if (!file_name)
		return (NULL);
	first = ft_extract_redir_tokens(current, file_name, first);
	node = malloc(sizeof(t_ast) * 1);
	if (!node)
		return (NULL);
	node->cmd_data = NULL;
	node->redir_data = malloc(sizeof(t_redir_data) * 1);
	if (!node->redir_data)
		return (free(node), NULL);
	if (current->type == TOK_REDIR_IN)
		ft_fill_redir(NODE_REDIR_IN, file_name->value, O_RDONLY, node);
	else if (current->type == TOK_REDIR_OUT)
		ft_fill_redir(NODE_REDIR_OUT, file_name->value, O_WRONLY | O_CREAT | O_TRUNC, node);
	else if (current->type == TOK_APPEND)
		ft_fill_redir(NODE_APPEND, file_name->value, O_WRONLY | O_CREAT | O_APPEND, node);
	else if (current->type == TOK_HEREDOC)
		ft_fill_redir(NODE_HEREDOC, file_name->value, O_RDONLY | O_CREAT | O_TRUNC, node);
	node->left = ft_create_tree(first, data);
	node->right = NULL;
	return (node);
}
