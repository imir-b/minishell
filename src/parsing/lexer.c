/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:55:33 by vbleskin          #+#    #+#             */
/*   Updated: 2026/04/27 13:53:32 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
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

char	*ft_extract_word(char *command_line, int *i)
{
	int	start;
	int	len;
	int	quote;

	start = *i;
	len = ((quote = 0));
	while (command_line[*i])
	{
		if ((command_line[*i] == '\'' || command_line[*i] == '\"')
			&& (!quote || quote == command_line[*i]))
			quote ^= command_line[*i];
		else if (!quote && (ft_is_space(command_line[*i])
				|| ft_is_in_charset(command_line[*i], "|<>&()")))
			break ;
		len++;
		(*i)++;
	}
	return (ft_substr(command_line, start, len));
}

char	*ft_extract_operator(char *command_line, int *i)
{
	int		start;
	int		len;
	char	*value;

	start = *i;
	len = 1;
	if ((command_line[*i] == '>' && command_line[*i + 1] == '>')
		|| (command_line[*i] == '<' && command_line[*i + 1] == '<')
		|| (command_line[*i] == '&' && command_line[*i + 1] == '&')
		|| (command_line[*i] == '|' && command_line[*i + 1] == '|'))
		len = 2;
	value = ft_substr(command_line, start, len);
	*i += len;
	return (value);
}
