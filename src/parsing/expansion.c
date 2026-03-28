/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:06:23 by vlad              #+#    #+#             */
/*   Updated: 2026/03/28 22:44:29 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// utiliser envp pour trouver la valeur de $variable,
// stocker et recuperer le code erreur de la derniere commande si ?$
// retier les quotes

char	*ft_remove_quotes(char **original)
{

}

static char	*ft_dup_key(char *cursor)
{
	char	*key;
	int		len;
	int		i;

	i = 0;
	if (*cursor == '$')
		cursor++;
	len = ft_key();
	key = malloc(sizeof(char) * (len + 1));
	if (!key)
		return (NULL);
	if (*cursor && *cursor >= 'A' && *cursor <= 'Z')
		key[i++] = (*cursor)++;
	while (*cursor && ((*cursor >= 'A' && *cursor <= 'Z')
			|| (*cursor >= '0' && *cursor <= '9')))
	{
		key[i++] = *cursor;
		cursor++;
	}
	return (key);
}

/*

Etape 1 : expand variables
Etape 2 : word splitting
Etape 3 : wildcards
Etape 4 : remove quotes

- Handle ’ (single quote) which should prevent the shell from 
interpreting the meta-characters in the quoted sequence.

- Handle " (double quote) which should prevent the shell from
interpreting the meta-characters in the quoted sequence except 
for $ (dollar sign)

*/

char	**ft_expand_variable(char *cursor, t_hash_table *h_map)
{
	t_env_node	*current;
	char		**args;
	char		*key;
	int			index;

	key = ft_dup_key(cursor);
	index = ft_hash_djb2(key) % HASH_SIZE;
	if (!h_map->items[index])
		return ;
	while (h_map->items[index] && ft_strcmp(h_map->items[index]->key, key))
		h_map->items[index] = h_map->items[index]->next;
	args = ft_split(h_map->items[index]->value, ' ');
	ft_remove_quotes(args);
	return (args);
}

/**
 * On navigue dans tout l'ast pour chercher des variables (qui commencent
 * par '$') et leur asigner leur valeur qui a ete stocke dans la hash map.
 */
void	ft_expand_tree(t_ast *node, t_hash_table *hash_map)
{
	char	*cursor;

	if (!node)
		return ;
	ft_expand_tree(node->left, hash_map);
	ft_expand_tree(node->right, hash_map);
	if (node->type == NODE_COMMAND)
	{
		cursor = ft_strchr(node->cmd_data->cmd, '$');
		if (cursor)
			ft_expand_variable(cursor, hash_map);
	}
	else if (node->type == NODE_REDIR_OUT || node->type == NODE_REDIR_IN
		|| node->type == NODE_APPEND)
	{
		cursor = ft_strchr(node->redir_data->file, '$');
		if (cursor)
			ft_expand_variable(cursor, hash_map);
	}
}
