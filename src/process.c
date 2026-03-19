/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 03:54:40 by vbleskin          #+#    #+#             */
/*   Updated: 2026/03/20 00:15:21 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_break_circle(t_token *first)
{
	first->prev->next = NULL;
	first->prev = NULL;
}

void	ft_parse_and_execute_command_line(char *command_line, t_minishell *data)
{
	t_token	*tokens;
	t_ast	*ast;

	tokens = ft_tokenizer(command_line);
	ft_print_tokens(tokens);
	ft_break_circle(tokens);
	ast = ft_create_tree(tokens);
	ft_expand(ast);
	ft_execute(ast, data);
}

void	ft_process_minishell(t_minishell *data)
{
	char	*command_line;

	while (1)
	{
		ft_setup_signals();
		command_line = readline("minishell>$ ");
		if (!command_line)
		{
			printf("exit\n");
			break ;
		}
		if (*command_line)
			add_history(command_line);
		ft_parse_and_execute_command_line(command_line, data);
		free(command_line);
	}
}
