/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:45:39 by vlad              #+#    #+#             */
/*   Updated: 2026/03/26 16:14:12 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_find_matching_paren(t_token *open_paren)
{
	t_token	*runner;
	int		count;

	if (!open_paren || open_paren->type != TOK_L_PAREN)
		return (NULL);
	runner = open_paren->next;
	count = 1;
	while (runner && count > 0)
	{
		if (runner->type == TOK_L_PAREN)
			count++;
		else if (runner->type == TOK_R_PAREN)
			count--;
		if (count > 0)
			runner = runner->next;
	}
	return (runner);
}

t_ast	*ft_create_subshell_node(t_token *current, t_minishell *data)
{
	t_ast	*node;
	t_token	*inside_content;
	t_token	*r_paren;

	r_paren = ft_find_matching_paren(current);
	if (!r_paren)
		return (ft_syntax_error("newline"), NULL);
	if (r_paren == current->next)
		return (ft_syntax_error(")"), NULL);
	inside_content = current->next;
	r_paren->prev->next = NULL;
	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_SUBSHELL;
	node->left = ft_create_tree(inside_content, data);
	free(current->value);
	free(current);
	free(r_paren->value);
	free(r_paren);
	if (!node->left)
		return (ft_free_ast(node), NULL);
	return (node);
}
