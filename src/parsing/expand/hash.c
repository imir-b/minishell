/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:33:28 by username          #+#    #+#             */
/*   Updated: 2026/04/07 14:35:50 by vbleskin         ###   ########.fr       */
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
	t_env_node		*new;
	t_env_node		*current;

	index = 0;
	new = malloc(sizeof(t_env_node) * 1);
	if (!new)
		return ;
	new->key = key;
	new->value = value;
	new->next = NULL;
	hash = ft_hash_djb2((unsigned char *)key);
	index = hash % HASH_SIZE;
	if (!items[index])
		items[index] = new;
	else
	{
		current = items[index];
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

static int	ft_key_len(char *str)
{
	int	i;

	i = 0;
	if (!str[i] || (!(str[i] >= 'a' && str[i] <= 'z')
			&& !(str[i] >= 'A' && str[i] <= 'Z') && str[i] != '_'))
		return (0);
	i++;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
		i++;
	return (i);
}

char	*ft_extract_key(char *str)
{
	char	*key;
	int		len;
	int		i;

	len = ft_key_len(str);
	if (len == 0)
		return (NULL);
	key = malloc(sizeof(char) * (len + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (i < len)
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

t_hash_table	*ft_init_hash_map(char **envp)
{
	t_hash_table	*hash_map;
	t_env_node		**items;
	char			*key;
	char			*value;
	int				count;

	items = ft_calloc(HASH_SIZE, sizeof(t_env_node *));
	if (!items)
		return (NULL);
	count = 0;
	while (envp[count])
	{
		key = ft_extract_key(envp[count]);
		value = ft_strdup((ft_strchr(envp[count], '=')) + 1);
		ft_fill_item(items, key, value);
		count++;
	}
	hash_map = malloc(sizeof(t_hash_table) * 1);
	if (!hash_map)
		return (free(items), NULL);
	hash_map->count = count;
	hash_map->items = items;
	hash_map->size = HASH_SIZE;
	return (hash_map);
}
