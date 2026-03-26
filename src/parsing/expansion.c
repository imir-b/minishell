/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:06:23 by vlad              #+#    #+#             */
/*   Updated: 2026/03/26 15:49:46 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// utiliser envp pour trouver la valeur de $variable, 
// stocker et recuperer le code erreur de la derniere commande si ?$
// retier les quotes

char	*ft_remove_quotes(char *original)
{
	char	*ret;
	int		len;

	len = ft_strlen(original);
	ret = malloc(sizeof(char) * (len - 1));
	return (ret);
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

/**
 * On navigue dans tout l'ast pour chercher des variables (qui commencent
 * par '$') et leur asigner leur valeur qui a ete stocke dans la hash map.
 */
void	ft_expand_tree(t_ast *node, t_hash_table *hash_map)
{
	if (!node)
		return ;
	ft_expand_tree(node->left, hash_map);
	ft_expand_tree(node->right, hash_map);
	if (node->type == NODE_COMMAND)
		;
	else if (node->type == NODE_REDIR_OUT || node->type == NODE_REDIR_IN
		|| node->type == NODE_APPEND)
		;
}
