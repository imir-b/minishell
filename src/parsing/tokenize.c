/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:01:31 by vlad              #+#    #+#             */
/*   Updated: 2026/03/15 16:54:38 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	*ft_free_tokens(t_token *tokens)
{
	t_token	*last;

	last = tokens->prev;
	while (tokens != last)
	{
		free(tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

t_token_type	ft_get_token_type(char *value)
{
	if (value[0] == '|' && value[1] == '|')
		return (OR_IF);
	else if (value[0] == '|')
		return (PIPE);
	else if (value[0] == '>' && value[1] == '>')
		return (APPEND);
	else if (value[0] == '>')
		return (REDIR_OUT);
	else if (value[0] == '<' && value[1] == '<')
		return (HEREDOC);
	else if (value[0] == '<')
		return (REDIR_IN);
	else if (value[0] == '&' && value[1] == '&')
		return (AND_IF);
	else if (value[0] == '(')
		return (L_PAREN);
	else if (value[0] == ')')
		return (R_PAREN);
	return (WORD);
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
		return ;
	}
	old_last = (*tokens)->prev;
	old_last->next = new_token;
	new_token->prev = old_last;
	(*tokens)->prev = new_token;
	new_token->next = tokens;
}

t_token	*ft_tokenizer(char *command_line)
{
	t_token	*tokens;
	t_token	*new_token;
	char	*value;
	int		i;

	tokens = NULL;
	i = 0;
	while (command_line[i])
	{
		if (ft_is_space(command_line[i]))
			i++;
		else if (ft_is_in_charset(command_line[i], "|<>&()"))
		{
			value = ft_extract_operator(command_line, &i);
			new_token = ft_new_token(value, ft_get_token_type(value));
			ft_token_add_back(&tokens, new_token);
		}
		else
		{
			value = ft_extract_word(command_line, &i);
			new_token = ft_new_token(value, WORD);
			ft_token_add_back(&tokens, new_token);
		}
	}
	return (tokens);
}
