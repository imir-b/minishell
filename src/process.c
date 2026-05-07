/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 03:54:40 by vbleskin          #+#    #+#             */
/*   Updated: 2026/05/08 00:58:46 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_is_operator(int type)
{
	return (type == TOK_PIPE || type == TOK_AND || type == TOK_OR);
}

int	ft_check_syntax(t_token *tokens)
{
	if (ft_is_operator(tokens->type))
		return (ft_syntax_error(tokens->value));
	while (tokens)
	{
		if (tokens->type == TOK_L_PAREN
			&& tokens->next->type == TOK_R_PAREN)
			return (ft_syntax_error(")"));
		if (tokens->type >= TOK_REDIR_IN && tokens->type <= TOK_HEREDOC)
		{
			if (!tokens->next || tokens->next->type != TOK_WORD)
				return (ft_syntax_error("newline or redirection file"));
		}
		if (ft_is_operator(tokens->type))
		{
			if (!tokens->next || ft_is_operator(tokens->next->type))
			{
				if (tokens->next)
					return (ft_syntax_error(tokens->next->value));
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
