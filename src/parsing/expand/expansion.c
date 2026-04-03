/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:06:23 by username          #+#    #+#             */
/*   Updated: 2026/04/03 14:52:35 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Etape 1 : expand variables
Etape 2 : word splitting
Etape 3 : wildcards
Etape 4 : remove quotes

// stocker et recuperer le code erreur de la derniere commande si ?$
*/

/*
- Handle ’ (single quote) which should prevent the shell from
interpreting the meta-characters in the quoted sequence.
- Handle " (double quote) which should prevent the shell from
interpreting the meta-characters in the quoted sequence except
for $ (dollar sign)
*/

char	*ft_expand_wildcards(char *original)
{
	
}

t_env_node	*ft_expand_variable(char *cursor, t_hash_table *h_map)
{
	t_env_node	*current;
	char		*key;
	int			index;

	key = ft_extract_key(cursor);
	index = ft_hash_djb2(key) % HASH_SIZE;
	if (!h_map->items[index])
		return (free(key), NULL);
	current = h_map->items[index];
	while (current && ft_strcmp(current->key, key) != 0)
		current = current->next;
	free(key);
	if (current)
		return (current);
	return (NULL);
}

int	ft_expanded_len(char *arg, t_hash_table *hash_map)
{
	int			i;
	int			single_quote;
	int			len;
	t_env_node	*var_data;

	((i = ((len = 0))));
	while (arg[i])
	{
		if (arg[i] == '\'')
			single_quote = !single_quote;
		if (arg[i] == '\'' || arg[i] == '\"') //verifier aussi qu on est pas dans des quotes pour pas skip les quotes dans les quotes
			i++;
		else if (arg[i] == '$' && !single_quote)
		{
			i++;
			var_data = ft_expand_variable(&(arg[i]), hash_map);
			i += ft_strlen(var_data->key);
			len += ft_strlen(var_data->value);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*ft_expand_single_arg(char *arg, t_hash_table *hash_map)
{
	t_env_node	*var_data;
	int			i;
	int			j;
	int			k;
	int			single_quote;
	int			len;
	char		*ret;

	((single_quote = ((i = ((j = 0))))));
	len = ft_expanded_len(arg, hash_map);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	while (arg[i])
	{
		if (arg[i] == '\'')
			single_quote = !single_quote;
		if (arg[i] == '\'' || arg[i] == '\"')
			i++;
		else if (arg[i] == '$' && !single_quote)
		{
			k = 0;
			i++;
			var_data = ft_expand_variable(&(arg[i]), hash_map);
			if (!var_data) // gerer differement si key n existe pas ?
				continue ;
			i += ft_strlen(var_data->key);
			while (var_data->value[k])
				ret[j++] = var_data->value[k++];
		}
		else
			ret[j++] = arg[i++];
	}
	ret[j] = '\0';
	return (ret);
}

/**
* On navigue dans tout l'ast pour chercher des variables (qui commencent
* par '$') et leur asigner leur valeur qui a ete stocke dans la hash map.
*/
void	ft_expand_tree(t_ast *node, t_hash_table *hash_map)
{
	int		i;

	if (!node)
		return ;
	ft_expand_tree(node->left, hash_map);
	ft_expand_tree(node->right, hash_map);
	i = 0;
	if (node->type == NODE_COMMAND)
	{
		while (node->cmd_data->args[i])
			ft_expand_single_arg(node->cmd_data->args[i++], hash_map);
	}
	else if (node->type == NODE_REDIR_OUT || node->type == NODE_REDIR_IN
		|| node->type == NODE_APPEND)
		ft_expand_single_arg(node->redir_data->file, hash_map);
}
