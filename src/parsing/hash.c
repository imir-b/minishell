/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:33:28 by vbleskin          #+#    #+#             */
/*   Updated: 2026/03/26 15:21:30 by vbleskin         ###   ########.fr       */
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

void	ft_fill_item(t_env_node **items, char *key, char *value)
{
	unsigned long	hash;
	int				index;

	index = 0;
	hash = ft_hash_djb2(key);
	index = hash % HASH_SIZE;
	if (!items[index])
		items[index] = (t_env_node *){key, value, NULL};
	else
	{
		while (items[index])
			items[index] = items[index]->next;
	}
}

char	*ft_dup_key(char *env)
{
	int		i;
	char	*key;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		key[i] = env[i];
	return (key);
}

t_hash_table	*ft_init_hash_map(char **envp)
{
	t_hash_table	*hash_map;
	t_env_node		**items;
	char			*key;
	char			*value;
	int				count;

	count = 0;
	while (envp[count])
	{
		key = ft_dup_key(envp[count]);
		value = ft_strdup((ft_strchr(envp[count], '=')) + 1);
		ft_fill_item(items, key, value);
		count++;
	}
	hash_map = (t_hash_table *){count, items, HASH_SIZE};
	return (hash_map);
}
