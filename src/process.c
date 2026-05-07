/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 03:54:40 by vbleskin          #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_ascii(void)
{
	printf("\033[35m       .             *              .              *\033[0m\n");
	printf("\033[35m  *           ☾             .               *              .\033[0m\n");
	printf("\033[33m      _____ _    _ ______ ______  ");
	printf("_____ _    _ ______ _      _\033[0m\n");
	printf("\033[33m     |_   _| |  | |  ____|  ____|/ ");
	printf("____| |  | |  ____| |    | |\033[0m\n");
	printf("\033[33m       | | | |  | | |__  | |__  | (");
	printf("___ | |__| | |__  | |    | |\033[0m\n");
	printf("\033[33m       | | | |  | |  __| |  __|  \\");
	printf("___ \\|  __  |  __| | |    | |\033[0m\n");
	printf("\033[33m       | | | |__| | |    | |     __");
	printf("__) | |  | | |____| |____| |____\033[0m\n");
	printf("\033[33m       |_|  \\____/|_|    |_|    |__");
	printf("___/|_|  |_|______|______|______|\033[0m\n");
	printf("\033[31m  .                               ");
	printf("                                       *\033[0m\n");
	printf("\033[31m        *             ☭             .");
	printf("             ☭              *\033[0m\n\n");
}

int	ft_check_unclosed_quotes(char *line)
{
	int		i;
	char	quote_type;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote_type = line[i];
			i++;
			while (line[i] != '\0' && line[i] != quote_type)
				i++;
			if (line[i] == '\0')
				return (ft_syntax_error("unclosed quote"), 1);
		}
		i++;
	}
	return (0);
}

static int	ft_check_syntax_ops(t_token *tokens)
{
	if (tokens->type == TOK_PIPE || tokens->type == TOK_AND
		|| tokens->type == TOK_OR)
	{
		if (!tokens->next || tokens->next->type == TOK_PIPE
			|| tokens->next->type == TOK_AND || tokens->next->type == TOK_OR)
		{
			if (tokens->next)
				return (ft_syntax_error(tokens->next->value));
			else
				return (ft_syntax_error("newline"));
		}
	}
	return (0);
}

int	ft_check_syntax(t_token *t)
{
	if (t->type == TOK_PIPE || t->type == TOK_AND || t->type == TOK_OR)
		return (ft_syntax_error(t->value));
	while (t)
	{
		if (t->type == TOK_L_PAREN && t->next->type == TOK_R_PAREN)
			return (ft_syntax_error(")"));
		if (t->type >= TOK_REDIR_IN && t->type <= TOK_HEREDOC)
		{
			if (!t->next || t->next->type != TOK_WORD)
				return (ft_syntax_error("newline or redirection file"));
		}
		if (ft_check_syntax_ops(t))
			return (1);
		t = t->next;
	}
	return (0);
}

int	ft_process_command_line(char *command_line, t_minishell *data)
{
	t_token	*tokens;

	if (ft_check_unclosed_quotes(command_line))
		return (1);
	tokens = ft_tokenizer(command_line);
	if (!tokens)
		return (1);
	ft_break_circle(tokens);
	if (ft_check_syntax(tokens))
		return (ft_free_tokens(tokens), 1);
	data->ast = ft_create_tree(tokens, data);
	if (!data->ast)
		return (1);
	if (ft_gather_heredocs(data->ast, data->hash_map))
		return (1);
	ft_execute(data);
	ft_free_ast(data->ast);
	data->ast = NULL;
	return (0);
}

void	ft_process_minishell(t_minishell *data)
{
	char	*command_line;

	while (1)
	{
		command_line = readline("minishell>$ ");
		if (!command_line)
		{
			printf("exit\n");
			break ;
		}
		if (*command_line)
			add_history(command_line);
		ft_process_command_line(command_line, data);
		free(command_line);
	}
}
