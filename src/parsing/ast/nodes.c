/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:46:41 by vlad              #+#    #+#             */
/*   Updated: 2026/03/26 16:10:32 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cut_list(t_token *op)
{
	if (op->prev)
		op->prev->next = NULL;
	if (op->next)
		op->next->prev = NULL;
}

t_ast	*ft_create_and_or_node(t_token *current, t_token *first,
			t_minishell *data)
{
	t_ast	*node;
	t_token	*first_right;

	first_right = current->next;
	ft_cut_list(current);
	if (first == current)
		first = NULL;
	node = malloc(sizeof(t_ast) * 1);
	if (!node)
		return (NULL);
	node->cmd_data = NULL;
	node->redir_data = NULL;
	if (current->type == TOK_AND)
		node->type = NODE_AND;
	else if (current->type == TOK_OR)
		node->type = NODE_OR;
	node->left = ft_create_tree(first, data);
	node->right = ft_create_tree(first_right, data);
	return (node);
}

t_ast	*ft_create_pipe_node(t_token *current, t_token *first,
			t_minishell *data)
{
	t_ast	*node;
	t_token	*first_right;

	first_right = current->next;
	ft_cut_list(current);
	if (first == current)
		first = NULL;
	node = malloc(sizeof(t_ast) * 1);
	if (!node)
		return (NULL);
	node->cmd_data = NULL;
	node->redir_data = NULL;
	node->type = NODE_PIPE;
	node->left = ft_create_tree(first, data);
	node->right = ft_create_tree(first_right, data);
	return (node);
}
