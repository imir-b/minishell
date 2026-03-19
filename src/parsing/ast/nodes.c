/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:46:41 by vlad              #+#    #+#             */
/*   Updated: 2026/03/20 00:46:47 by vlad             ###   ########.fr       */
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

t_ast	*ft_create_and_or_node(t_token *current, t_token *first)
{
	t_ast	*node;
	t_token	*first_right;

	ft_cut_list(current);
	node = malloc(sizeof(t_ast) * 1);
	if (!node)
		return (NULL);
	if (current->type == TOK_AND)
		node->type = NODE_AND;
	else if (current->type == TOK_OR)
		node->type = NODE_OR;
	node->left = ft_create_tree(first);
	node->right = ft_create_tree(current->next);
	return (node);
}

t_ast	*ft_create_pipe_node(t_token *current, t_token *first)
{
	t_ast	*node;
	t_token	*first_right;

	ft_cut_list(current);
	node = malloc(sizeof(t_ast) * 1);
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->left = ft_create_tree(first);
	node->right = ft_create_tree(first_right);
	return (node);
}

t_ast	*ft_create_subshell_node(t_token *current, t_token *first)
{
	t_ast	*node;
	t_token	*first_right;

	ft_cut_list(current);
	node = malloc(sizeof(t_ast) * 1);
	if (!node)
		return (NULL);
	node->type = NODE_SUBSHELL;
	node->left = ft_create_tree(first);
	node->right = ft_create_tree(current->next);
	return (node);
}
