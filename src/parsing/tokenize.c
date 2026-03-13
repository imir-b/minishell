/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:01:31 by vlad              #+#    #+#             */
/*   Updated: 2026/03/11 23:05:34 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

TokenType	ft_get_token_type(char *value)
{
	if (value[0] == '|')
		return (PIPE);
	else if (value[0] == '>' && value[1] == '>')
		return (APPEND);
	else if (value[0] == '>')
		return (REDIR_OUT);
	else if (value[0] == '<')
		return (REDIR_IN);
	return (WORD);
}

t_token	*ft_new_token(char *value, TokenType type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	ft_token_add_back(t_token **tokens, t_token *new_token)
{
	t_token	*temp;

	if (!tokens || !new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	temp = *tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
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
		else if (ft_is_special_char(command_line[i]))
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
