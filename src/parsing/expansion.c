/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:06:23 by vlad              #+#    #+#             */
/*   Updated: 2026/03/18 04:34:48 by vbleskin         ###   ########.fr       */
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

// this algorithm (k=33) was first reported by dan bernstein many years ago in 
// comp.lang.c. another version of this algorithm (now favored by bernstein) 
// uses xor: hash(i) = hash(i - 1) * 33 ^ str[i]; the magic of number 33 (why 
// it works better than many other constants, prime or not) has never been 
// adequately explained.

//     unsigned long
//     hash(unsigned char *str)
//     {
//         unsigned long hash = 5381;
//         int c;

//         while (c = *str++)
//             hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

//         return hash;
//     }

// expendre une variable pour trouver sa valeur grace a une hash map
void	ft_djb2()
{

}

void	ft_expand_variables(t_ast *ast, t_minishell *data)
{
	(void)ast;
	(void)data;
}
