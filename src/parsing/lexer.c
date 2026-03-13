/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2026/03/09 11:01:31 by vlad              #+#    #+#             */
/*   Updated: 2026/03/11 02:31:48 by vbleskin         ###   ########.fr       */
=======
/*   Created: 2026/03/11 23:05:14 by vlad              #+#    #+#             */
/*   Updated: 2026/03/11 23:06:22 by vlad             ###   ########.fr       */
>>>>>>> 3ff19a02160bc41edfa8b454a2b9cca46e3f9ed4
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);

int	ft_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_is_special_char(char c)
{
<<<<<<< HEAD
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
	t_token	*token;
	int		j;
	char	*value;

	j = 0;
	while (command_line[*i])
		value[j++] = command_line[(*i)++];
	token = (t_token *){WORD, value, NULL};
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
=======
	if (c == '|' || c == '>' || c == '<')
		return (1);
>>>>>>> 3ff19a02160bc41edfa8b454a2b9cca46e3f9ed4
	return (0);
}

char	*ft_extract_word(char *command_line, int *i)
{
	int		start;
	int		len;
	char	*value;

	start = *i;
	len = 0;
	if (command_line[*i] == '\"')
	{
		start++;
		(*i)++;
		while (command_line[*i] && command_line[*i] != '\"')
		{
			len++;
			(*i)++;
		}
		if (command_line[*i] == '\"')
			(*i)++;
	}
	else
	{
		while (command_line[*i] && !ft_is_space(command_line[*i])
			&& !ft_is_special_char(command_line[*i]))
		{
			len++;
			(*i)++;
		}
	}
	value = ft_substr(command_line, start, len);
	return (value);
}

char	*ft_extract_operator(char *command_line, int *i)
{
	int		start;
	int		len;
	char	*value;

	start = *i;
	len = 1;
	if ((command_line[*i] == '>' && command_line[*i + 1] == '>')
		|| (command_line[*i] == '<' && command_line[*i + 1] == '<'))
		len = 2;
	value = ft_substr(command_line, start, len);
	*i += len;
	return (value);
}
