/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:06:23 by username          #+#    #+#             */
/*   Updated: 2026/04/27 14:08:47 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Etape 1 : expand variables
Etape 2 : word splitting
Etape 3 : wildcards
Etape 4 : remove quotes

// TODO ->>>> stocker et recuperer le code erreur de la derniere commande si ?$
*/

/*
- Handle ’ (single quote) which should prevent the shell from
interpreting the meta-characters in the quoted sequence.
- Handle " (double quote) which should prevent the shell from
interpreting the meta-characters in the quoted sequence except
for $ (dollar sign)
*/

int	ft_check_ambiguous_redirect(char *expanded_file)
{
	int	i;
	int	quotes;

	if (expanded_file[0] == '\0')
		return (1);
	i = 0;
	quotes = 0;
	while (expanded_file[i])
	{
		if ((expanded_file[i] == '\'' || expanded_file[i] == '\"')
			&& (!quotes || quotes == expanded_file[i]))
		{
			quotes ^= expanded_file[i];
		}
		if ((expanded_file[i] == ' ' || expanded_file[i] == '\t') && !quotes)
			return (1);
		i++;
	}
	return (0);
}

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
	i = 0;
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
	char	*original;
	char	*new;

	original = ft_strdup(node->redir_data->file);
	new = ft_expand_single_arg(node->redir_data->file, map);
	free(node->redir_data->file);
	node->redir_data->file = new;
	if (ft_check_ambiguous_redirect(node->redir_data->file))
		return (ft_ambiguous_redirect_err(original));
	node->redir_data->file = ft_remove_quotes(node->redir_data->file);
	free(original);
	return (0);
}

/**
* On navigue dans tout l'ast pour chercher des variables (qui commencent
* par '$') et leur asigner leur valeur qui a ete stocke dans la hash map.
*/

int	ft_expand_tree(t_ast *node, t_hash_table *hash_map)
{
	if (!node)
		return (0);
	ft_expand_tree(node->left, hash_map);
	ft_expand_tree(node->right, hash_map);
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
