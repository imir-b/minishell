/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:01:31 by username          #+#    #+#             */
/*   Updated: 2026/04/03 01:42:01 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (value[0] == '&' && value[1] == '\0')
			{
				ft_syntax_error("&");
				free(value);
				return (ft_free_tokens(tokens));
			}
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
