/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:01:31 by username          #+#    #+#             */
/*   Updated: 2026/05/08 01:58:32 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	ft_handle_operator(char *line, int *i, t_token **tokens)
{
	char	*val;
	t_token	*new;

	val = ft_extract_operator(line, i);
	if (val[0] == '&' && val[1] == '\0')
	{
		ft_syntax_error("&");
		free(val);
		return (1);
	}
	new = ft_new_token(val, ft_get_token_type(val));
	ft_token_add_back(tokens, new);
	return (0);
}

t_token	*ft_tokenizer(char *command_line)
{
	t_token	*tokens;
	t_token	*new;
	char	*val;
	int		i;

	tokens = NULL;
	i = 0;
	while (command_line[i])
	{
		if (ft_is_space(command_line[i]))
			i++;
		else if (ft_is_in_charset(command_line[i], "|<>&()"))
		{
			if (ft_handle_operator(command_line, &i, &tokens))
				return (ft_free_tokens(tokens));
		}
		else
		{
			val = ft_extract_word(command_line, &i);
			new = ft_new_token(val, TOK_WORD);
			ft_token_add_back(&tokens, new);
		}
	}
	return (tokens);
}

t_token	*ft_token_last(t_token *first)
{
	t_token	*last;

	/* Fix: Added NULL check to prevent segfault when no tokens are left
	   (e.g., during redirections without commands) */
	if (!first)
		return (NULL);
	last = first;
	while (last->next)
		last = last->next;
	return (last);
}
