/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:01:31 by vlad              #+#    #+#             */
/*   Updated: 2026/03/09 14:45:52 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_add_token(t_token *current, t_token *list)
{
	
}

void	ft_tokenize_quotes_word(char *command_line, int *i, t_token *tokens)
{
	t_token	*token;
	char	*value;
	int		j;

	ft_create_token();
	j = 0;
	if (command_line[*i] == '\"')
		(*i)++;
	while (command_line[*i] && (command_line[*i] != '\"'))
		value[j++] = command_line[(*i)++];
	token = (t_token *){WORD, value, NULL};
	ft_add_token(token, tokens);
}

void	ft_tokenize_word(char *command_line, int *i, t_token *tokens)
{
	
}

void	ft_tokenize_special_char(char *command_line, int *i, t_token *tokens)
{
	t_token	*token;

	if (command_line[*i] == '|')
		token = (t_token *){PIPE, NULL, NULL};
	else if (command_line[*i] == '>')
	{
		if (command_line[(*i) + 1] == '>')
		{
			token = (t_token *){APPEND, NULL, NULL};
			(*i)++;
		}
		else
			token = (t_token *){REDIR_OUT, NULL, NULL};
	}
	else if (command_line[*i] == '<')
		token = (t_token *){REDIR_IN, NULL, NULL};
	(*i)++;
	ft_add_token(token, tokens);
}

/**
 * Fonction utilitaire qui cherche 'c' dans 'charset' et renvoie 1 si trouve.
 */
int	ft_is_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

/**
 * Créé un token pour chaque "mot" de la ligne de commande
 */
t_token	*ft_tokenizer(char *command_line)
{
	t_token	*tokens;
	int		i;

	tokens = (t_token *){0, NULL, NULL};
	i = 0;
	while (command_line[i])
	{
		if (ft_is_space(command_line[i]))
		{
			i++;
			if (!command_line[i])
				break ;
		}
		else if (ft_is_in_charset(command_line[i], "|<>"))
			ft_tokenize_special_char(command_line, &i, tokens);
		else if (command_line[i] == '\"')
			ft_tokenize_quotes_word(command_line, &i, tokens);
		else
			ft_tokenize_word(command_line, &i, tokens);
	}
	return (tokens);
}
