/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:06:23 by vlad              #+#    #+#             */
/*   Updated: 2026/03/25 13:26:36 by vlad             ###   ########.fr       */
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

//  Handle ’ (single quote) which should prevent the shell from interpreting the meta-
// characters in the quoted sequence.
// • Handle " (double quote) which should prevent the shell from interpreting the meta-
// characters in the quoted sequence except for $ (dollar sign)



/**
 * this algorithm (k=33) was first reported by dan bernstein many years ago in 
 * comp.lang.c. another version of this algorithm (now favored by bernstein) 
 * uses xor: hash(i) = hash(i - 1) * 33 ^ str[i]; the magic of number 33 (why 
 * it works better than many other constants, prime or not) has never been 
 * adequately explained.
 */
unsigned long	ft_hash_djb2(unsigned char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while (*str)
	{
		c = *str;
		hash =  ((hash << 5) + hash) + c;
		str++;
	}
	return (hash);
}

// index = hash % table_size
void	ft_expand_variables(t_ast *ast, t_minishell *data)
{
	if (ast->type == NODE_COMMAND || ast->type == NODE_REDIR_OUT 
		|| ast->type == NODE_REDIR_IN || ast->type == NODE_APPEND)
	{
		//rechercher si on a des valeurs qui commencent par $, si oui, chercher la valeur correspondante dans la hash map
	}
	(void)data;
}
