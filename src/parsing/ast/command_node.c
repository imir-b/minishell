/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:40:04 by vlad              #+#    #+#             */
/*   Updated: 2026/03/20 00:42:17 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **ft_create_args(t_token *first)
{
    
}

char    *ft_find_cmd_path(char **paths, char *cmd)
{
    
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
	node->cmd_data->cmd = first->value;
	node->cmd_data->args = ft_create_args(first);
	node->cmd_data->path = ft_find_cmd_path(data->paths, first->value);
	return (node);
}
