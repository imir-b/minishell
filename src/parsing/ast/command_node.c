/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:40:04 by vlad              #+#    #+#             */
/*   Updated: 2026/04/07 14:50:43 by vbleskin         ###   ########.fr       */
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

static char	*ft_find_cmd_path(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	full_path = NULL;
	i = 0;
	if (ft_strrchr(cmd, '/') && access(cmd, X_OK) == 0)
		full_path = ft_strdup(cmd);
	else
	{
		while (paths && paths[i])
		{
			full_path = ft_super_join(paths[i], cmd, '/');
			if (full_path && access(full_path, X_OK) == 0)
				break ;
			free(full_path);
			i++;
		}
	}
	return (full_path);
}

t_ast	*ft_create_command_node(t_token *first, t_minishell *data)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast) * 1);
	if (!node)
		return (NULL);
	node->type = NODE_COMMAND;
	node->cmd_data = malloc(sizeof(t_cmd_data) * 1);
	if (!node->cmd_data)
		return (free(node), NULL);
	node->cmd_data->args = ft_create_args(first);
	node->cmd_data->cmd = node->cmd_data->args[0];
	node->cmd_data->path = ft_find_cmd_path(data->paths, first->value);
	node->left = NULL;
	node->right = NULL;
	node->redir_data = NULL;
	return (node);
}
