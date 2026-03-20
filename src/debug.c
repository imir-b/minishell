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

void	ft_print_ast(t_ast *node, int level)
{
	int	i;

	if (!node)
		return ;
	ft_print_ast(node->right, level + 1);
	i = 0;
	while (i++ < level)
		printf("                 ");
	if (node->type == NODE_PIPE)
		printf("[ NODE_PIPE ]\n");
	else if (node->type == NODE_AND)
		printf("[ NODE_AND ]\n");
	else if (node->type == NODE_OR)
		printf("[ NODE_OR ]\n");
	else if (node->type == NODE_SUBSHELL)
		printf("[ NODE_SUBSHELL ]\n");
	else if (node->type >= NODE_REDIR_IN && node->type <= NODE_HEREDOC)
	{
		char *t = "REDIR_IN (<)";
		if (node->type == NODE_REDIR_OUT) t = "REDIR_OUT (>)";
		else if (node->type == NODE_APPEND) t = "REDIR_APPEND (>>)";
		else if (node->type == NODE_HEREDOC) t = "HEREDOC (<<)";
		printf("[ %s ]\n", t);
		i = 0; while (i++ < level) printf("                 ");
		printf("  fichier: \"%s\"\n", node->redir_data->file);
		i = 0; while (i++ < level) printf("                 ");
		printf("  flags: ");
		if (node->type == NODE_REDIR_IN) printf("O_RDONLY\n");
		else if (node->type == NODE_REDIR_OUT) printf("O_TRUNC | O_CREAT | O_WRONLY\n");
		else if (node->type == NODE_APPEND) printf("O_APPEND | O_CREAT | O_WRONLY\n");
		else if (node->type == NODE_HEREDOC) printf("O_RDONLY | O_CREAT | O_TRUNC\n");
	}
	else if (node->type == NODE_COMMAND)
	{
		printf("[ NODE_COMMAND ]\n");
		i = 0; while (i++ < level) printf("                 ");
		printf("  cmd: \"%s\"\n", node->cmd_data->cmd);
		i = 0; while (i++ < level) printf("                 ");
		printf("  args: [");
		int j = 0;
		while (node->cmd_data->args && node->cmd_data->args[j])
		{
			printf("\"%s\"", node->cmd_data->args[j]);
			if (node->cmd_data->args[j + 1])
				printf(", ");
			j++;
		}
		printf("]\n");
	}
	ft_print_ast(node->left, level + 1);
}
