/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:01:31 by vlad              #+#    #+#             */
/*   Updated: 2026/03/18 23:16:23 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	*ft_free_tokens(t_token *tokens)
{
	t_token	*last;
	t_token	*next_node;

	if (!tokens)
		return (NULL);
	last = tokens->prev;
	while (1)
	{
		next_node = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		if (tokens == last)
			break ;
		tokens = next_node;
	}
	return (NULL);
}

t_token_type	ft_get_token_type(char *value)
{
	if (value[0] == '|' && value[1] == '|')
		return (TOK_OR);
	else if (value[0] == '|')
		return (TOK_PIPE);
	else if (value[0] == '>' && value[1] == '>')
		return (TOK_APPEND);
	else if (value[0] == '>')
		return (TOK_REDIR_OUT);
	else if (value[0] == '<' && value[1] == '<')
		return (TOK_HEREDOC);
	else if (value[0] == '<')
		return (TOK_REDIR_IN);
	else if (value[0] == '&' && value[1] == '&')
		return (TOK_AND);
	else if (value[0] == '(')
		return (TOK_L_PAREN);
	else if (value[0] == ')')
		return (TOK_R_PAREN);
	return (TOK_WORD);
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
			new_token = ft_new_token(value, TOK_WORD);
			ft_token_add_back(&tokens, new_token);
		}
	}
	return (tokens);
}
