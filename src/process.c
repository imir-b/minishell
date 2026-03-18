/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 03:54:40 by vbleskin          #+#    #+#             */
/*   Updated: 2026/03/18 04:51:21 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_and_execute_command_line(char *command_line, t_minishell *data)
{
	t_token	*tokens;
	t_ast	*ast;

	tokens = ft_tokenizer(command_line);
	ast = ft_create_tree(tokens);
	(void)data;
	// ft_execute(ast, data);
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
