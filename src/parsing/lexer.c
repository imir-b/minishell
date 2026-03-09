/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:01:31 by vlad              #+#    #+#             */
/*   Updated: 2026/03/09 12:07:19 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_create_token(t_token *tokens)
{
	
}

void	ft_tokenize_word(char *command_line, int *i, t_token *token)
{
	char	*value;
	int		j;

	j = 0;
	if (command_line[*i] == '\"')
		(*i)++;
	while (command_line[*i] != '\"')
		value[j++] = command_line[(*i)++];
	token = (t_token *){WORD, value, (void *)0};
}

void	ft_tokenize_special_char(char *command_line, int *i, t_token *token)
{
	if (command_line[*i] == '|')
		token = (t_token *){PIPE, (void *)0, (void *)0};
	else if (command_line[*i] == '>')
	{
		if (command_line[(*i) + 1] == '>')
		{
			token = (t_token *){APPEND, (void *)0, (void *)0};
			(*i)++;	
		}
		else
			token = (t_token *){REDIR_OUT, (void *)0, (void *)0};
	}
	else if (command_line[*i] == '<')
		token = (t_token *){REDIR_IN, (void *)0, (void *)0};
	(*i)++;
}

int	ft_is_special_char(char *command_line, int i)
{
	if (command_line[i] == '|' 
		|| command_line[i] == '>' 
		|| command_line[i] == '<')
		return (1);
	return (0);
}

/**
 * Créé un token pour chaque "mot" de la ligne de commande
 */
t_token	*ft_tokenizer(char *command_line)
{
	t_token	*tokens;
	t_token	*current;
    int		i;

	i = 0;
	while (command_line[i])
	{
		if (ft_is_space(command_line[i]))
		{
			i++;
			if (!command_line[i])
				break ;
		}
		else if (ft_is_special_char(command_line, i))
			ft_tokenize_special_char(command_line, &i, tokens);
		else if (command_line[i] == '\"')
			ft_tokenize_word(command_line, &i, tokens);
	}
	return (tokens);
}
