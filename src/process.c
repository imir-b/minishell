/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 03:54:40 by vbleskin          #+#    #+#             */
/*   Updated: 2026/03/20 02:16:46 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_error(char *token_value)
{
	ft_putstr_fd("syntax error near unexpected token '", STDERR_FILENO);
	ft_putstr_fd(token_value, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (1);
}

int	ft_check_syntax(t_token *tokens)
{
	if (tokens->type == TOK_PIPE || tokens->type == TOK_AND || tokens->type == TOK_OR)
        return (ft_syntax_error(tokens->value));
    while (tokens)
    {
        if (tokens->type >= TOK_REDIR_IN && tokens->type <= TOK_HEREDOC)
        {
            if (!tokens->next || tokens->next->type != TOK_WORD)
                return (ft_syntax_error("newline or redirection file"));
        }
        if (tokens->type == TOK_PIPE || tokens->type == TOK_AND || tokens->type == TOK_OR)
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
        tokens = tokens->next;
    }
    return (0);
}

void	ft_parse_and_execute_command_line(char *command_line, t_minishell *data)
{
	t_token	*tokens;

	tokens = ft_tokenizer(command_line);
	ft_print_tokens(tokens); // debug
	ft_break_circle(tokens);
	if (ft_check_syntax(tokens))
	{
		ft_free_tokens(tokens);
		return ;
	}
	data->ast = ft_create_tree(tokens, data);
	if (!data->ast)
		return ;
	printf("\n--- AST ---\n"); // debug
	ft_print_ast(data->ast, 0); // debug
	printf("-----------\n\n"); // debug
	ft_expand_variables(data->ast, data);
	ft_execute(data);
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
