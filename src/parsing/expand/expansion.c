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

/*
Etape 1 : expand variables
Etape 2 : word splitting
Etape 3 : wildcards
Etape 4 : remove quotes
*/

/*
- Handle ’ (single quote) which should prevent the shell from
interpreting the meta-characters in the quoted sequence.
- Handle " (double quote) which should prevent the shell from
interpreting the meta-characters in the quoted sequence except
for $ (dollar sign)
*/

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

static int	ft_expand_redir_node(t_ast *node, t_hash_table *map)
{
	char	*orig;
	char	*new;
	char	**temp;
	char	**split;
	char	**wild_exp;
	int		count;

	orig = ft_strdup(node->redir_data->file);
	new = ft_expand_single_arg(node->redir_data->file, map);
	temp = malloc(sizeof(char *) * 2);
	if (!temp)
		return (free(orig), free(new), 1);
	(temp[0] = new, temp[1] = NULL);
	split = ft_word_splitting(temp);
	wild_exp = ft_expand_wildcards(split);
	count = 0;
	while (wild_exp && wild_exp[count])
		count++;
	if (count != 1)
		return (ft_free_tab(wild_exp), ft_ambiguous_redirect_err(orig),
			free(orig), 1);
	free(node->redir_data->file);
	node->redir_data->file = ft_remove_quotes(wild_exp[0]);
	return (ft_free_tab(wild_exp), free(orig), 0);
}

/**
* ft_expand_node - Expands variables, wildcards and removes quotes for a single node.
* This is called during execution to ensure environment changes are reflected.
*/
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
