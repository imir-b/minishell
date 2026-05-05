/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:40:04 by vlad              #+#    #+#             */
/*   Updated: 2026/04/26 17:17:13 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_create_args(t_token *first)
{
	t_token	*current;
	char	**args;
	int		count;

	current = first;
	count = 0;
	while (current && current->type == TOK_WORD)
	{
		count++;
		current = current->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	current = first;
	count = 0;
	while (current && current->type == TOK_WORD)
	{
		args[count++] = ft_strdup(current->value);
		current = current->next;
	}
	args[count] = NULL;
	return (args);
}

t_ast	*ft_create_command_node(t_token *first, t_minishell *data)
{
	t_ast	*node;

	(void)data;
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_COMMAND;
	node->cmd_data = malloc(sizeof(t_cmd_data));
	if (!node->cmd_data)
		return (free(node), NULL);
	node->cmd_data->args = ft_create_args(first);
	node->cmd_data->cmd = node->cmd_data->args[0];
	node->cmd_data->path = NULL;
	node->left = NULL;
	node->right = NULL;
	node->redir_data = NULL;
	ft_free_tokens(first);
	return (node);
}
