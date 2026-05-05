/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:05:19 by vlad              #+#    #+#             */
/*   Updated: 2026/04/26 17:46:33 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_find_operator(t_token *first, t_token_type type1,
					t_token_type type2)
{
	t_token	*current;
	int		paren;

	paren = 0;
	current = ft_token_last(first);
	while (current)
	{
		if (current->type == TOK_R_PAREN)
			paren++;
		else if (current->type == TOK_L_PAREN)
			paren--;
		if (paren == 0 && current->type >= type1 && current->type <= type2)
			return (current);
		current = current->prev;
	}
	return (NULL);
}

t_ast	*ft_create_tree(t_token *first, t_minishell *data)
{
	t_token	*op;

	if (!first)
		return (NULL);
	op = ft_find_operator(first, TOK_AND, TOK_OR);
	if (op)
		return (ft_create_and_or_node(op, first, data));
	op = ft_find_operator(first, TOK_PIPE, TOK_PIPE);
	if (op)
		return (ft_create_pipe_node(op, first, data));
	op = ft_find_operator(first, TOK_REDIR_IN, TOK_HEREDOC);
	if (op)
		return (ft_create_redir_node(op, first, data));
	op = ft_find_operator(first, TOK_L_PAREN, TOK_L_PAREN);
	if (op)
	{
		if (op != first)
			return (ft_syntax_error(op->value), NULL);
		return (ft_create_subshell_node(op, data));
	}
	return (ft_create_command_node(first, data));
}
