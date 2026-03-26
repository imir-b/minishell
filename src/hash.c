/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:33:28 by vbleskin          #+#    #+#             */
/*   Updated: 2026/03/26 12:32:16 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		hash = ((hash << 5) + hash) + c;
		str++;
	}
	return (hash);
}

t_hash_table	*ft_init_hash_map(char **envp)
{
	t_hash_table	*hash_map;
	t_env_node		**items;
	int				index;
	unsigned long	hash;

	while (envp)
	{

		index = hash % HASH_SIZE;
		if (items[index])
			items[index] = ft_find_next_empty();
		items[index] = ;
	}
	hash_map = (t_hash_table *){0, items, HASH_SIZE};
	return (hash_map);
}
