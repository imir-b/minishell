/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:05:14 by vlad              #+#    #+#             */
/*   Updated: 2026/03/11 23:06:22 by vlad             ###   ########.fr       */
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
	if (c == '|' || c == '>' || c == '<')
		return (1);
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
