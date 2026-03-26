/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:45:51 by vlad              #+#    #+#             */
/*   Updated: 2026/03/26 15:41:17 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_break_circle(t_token *first)
{
	first->prev->next = NULL;
	first->prev = NULL;
}

void	*ft_free_tokens(t_token *tokens)
{
	t_token	*tmp;

	if (!tokens)
		return (NULL);
	if (tokens->prev)
		ft_break_circle(tokens);
	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
	return (NULL);
}

t_token	*ft_new_token(char *value, t_token_type type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	ft_token_add_back(t_token **tokens, t_token *new_token)
{
	t_token	*old_last;

	if (!tokens || !new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		new_token->next = new_token;
		new_token->prev = new_token;
		return ;
	}
	old_last = (*tokens)->prev;
	old_last->next = new_token;
	new_token->prev = old_last;
	new_token->next = *tokens;
	(*tokens)->prev = new_token;
}
