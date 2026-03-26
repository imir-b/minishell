/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 03:54:40 by vbleskin          #+#    #+#             */
/*   Updated: 2026/03/26 15:28:16 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Affiche le bandeau ascii au lancement de minishell
 */
void	ft_print_ascii(void)
{
	write(1, "MINISHELL\n", 10);
}

int	ft_check_syntax(t_token *tokens)
{
	if (tokens->type == TOK_PIPE || tokens->type == TOK_AND
		|| tokens->type == TOK_OR)
		return (ft_syntax_error(tokens->value));
	while (tokens)
	{
		if (tokens->type >= TOK_REDIR_IN && tokens->type <= TOK_HEREDOC)
		{
			if (!tokens->next || tokens->next->type != TOK_WORD)
				return (ft_syntax_error("newline or redirection file"));
		}
		if (tokens->type == TOK_PIPE || tokens->type == TOK_AND
			|| tokens->type == TOK_OR)
		{
			if (!tokens->next || tokens->next->type == TOK_PIPE
				|| tokens->next->type == TOK_AND
				|| tokens->next->type == TOK_OR)
			{
				if (tokens->next)
					return (ft_syntax_error(tokens->next->value));
				else
					return (ft_syntax_error("newline"));
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

int	ft_process_command_line(char *command_line, t_minishell *data)
{
	t_token	*tokens;

	tokens = ft_tokenizer(command_line);
	if (!tokens)
		return (1);
	// ft_print_tokens(tokens); // debug
	ft_break_circle(tokens);
	if (ft_check_syntax(tokens))
		return (ft_free_tokens(tokens), 1);
	data->ast = ft_create_tree(tokens, data);
	if (!data->ast)
		return (ft_free_tokens(tokens), 1);
	// printf("\n--- AST ---\n"); // debug
	// ft_print_ast(data->ast, 0); // debug
	// printf("-----------\n\n"); // debug
	ft_free_tokens(tokens);
	ft_expand_tree(data->ast, data->hash_map);
	ft_execute(data);
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
