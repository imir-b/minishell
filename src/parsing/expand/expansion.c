/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:06:23 by username          #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_expand_cmd_node(t_ast *node, t_hash_table *map)
{
	int		i;
	char	*new;

	i = 0;
	while (node->cmd_data->args[i])
	{
		new = ft_expand_single_arg(node->cmd_data->args[i], map);
		free(node->cmd_data->args[i]);
		node->cmd_data->args[i++] = new;
	}
	node->cmd_data->args = ft_word_splitting(node->cmd_data->args);
	node->cmd_data->args = ft_expand_wildcards(node->cmd_data->args);
	node->cmd_data->args = ft_remove_quotes_array(node->cmd_data->args);
	if (node->cmd_data->args && node->cmd_data->args[0])
		node->cmd_data->cmd = node->cmd_data->args[0];
	else
		node->cmd_data->cmd = NULL;
	return (0);
}

static int	ft_get_word_count(char **args)
{
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}

static int	ft_expand_redir_node(t_ast *node, t_hash_table *map)
{
	char	*orig;
	char	*new;
	char	**temp;
	char	**split;
	char	**wild_exp;

	orig = ft_strdup(node->redir_data->file);
	new = ft_expand_single_arg(node->redir_data->file, map);
	temp = malloc(sizeof(char *) * 2);
	if (!temp)
		return (free(orig), free(new), 1);
	(temp[0] = new, temp[1] = NULL);
	split = ft_word_splitting(temp);
	wild_exp = ft_expand_wildcards(split);
	if (ft_get_word_count(wild_exp) != 1)
	{
		ft_free_tab(wild_exp);
		ft_ambiguous_redirect_err(orig);
		return (free(orig), 1);
	}
	free(node->redir_data->file);
	node->redir_data->file = ft_remove_quotes(wild_exp[0]);
	return (ft_free_tab(wild_exp), free(orig), 0);
}

int	ft_expand_node(t_ast *node, t_hash_table *hash_map)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
	{
		if (ft_expand_cmd_node(node, hash_map))
			return (1);
	}
	else if (node->type == NODE_REDIR_OUT || node->type == NODE_REDIR_IN
		|| node->type == NODE_APPEND)
	{
		if (ft_expand_redir_node(node, hash_map))
			return (1);
	}
	return (0);
}
