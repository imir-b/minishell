/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@gemini.ai>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 21:00:00 by antigravity     #+#    #+#             */
/*   Updated: 2026/03/19 21:00:00 by antigravity    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tokens(t_token *tokens)
{
	t_token	*current;
	char	*type_str;

	if (!tokens)
		return ;
	current = tokens;
	printf("--- TOKENS LIST ---\n");
	do
	{
		if (current->type == TOK_WORD)
			type_str = "WORD";
		else if (current->type == TOK_PIPE)
			type_str = "PIPE (|)";
		else if (current->type == TOK_REDIR_IN)
			type_str = "REDIR_IN (<)";
		else if (current->type == TOK_REDIR_OUT)
			type_str = "REDIR_OUT (>)";
		else if (current->type == TOK_APPEND)
			type_str = "APPEND (>>)";
		else if (current->type == TOK_HEREDOC)
			type_str = "HEREDOC (<<)";
		else if (current->type == TOK_AND)
			type_str = "AND (&&)";
		else if (current->type == TOK_OR)
			type_str = "OR (||)";
		else if (current->type == TOK_L_PAREN)
			type_str = "L_PAREN ( ( )";
		else if (current->type == TOK_R_PAREN)
			type_str = "R_PAREN ( ) )";
		else
			type_str = "UNKNOWN";

		if (current->value)
			printf("Type: %-15s | Value: \"%s\"\n", type_str, current->value);
		else
			printf("Type: %-15s | Value: NULL\n", type_str);
		current = current->next;
	} while (current != tokens);
	printf("-------------------\n");
}
