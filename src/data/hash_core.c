/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:00:00 by gemini            #+#    #+#             */
/*   Updated: 2026/05/07 11:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char			*equal;

	hash_map = malloc(sizeof(t_hash_table));
	if (!hash_map)
		return (NULL);
	hash_map->items = ft_calloc(HASH_SIZE, sizeof(t_env_node *));
	if (!hash_map->items)
		return (free(hash_map), NULL);
	hash_map->size = HASH_SIZE;
	hash_map->count = 0;
	while (envp && *envp)
	{
		equal = ft_strchr(*envp, '=');
		if (equal)
		{
			ft_hash_table_insert(hash_map, ft_substr(*envp, 0,
					equal - *envp), ft_strdup(equal + 1), 1);
			hash_map->count++;
		}
		envp++;
	}
	ft_update_shlvl(hash_map);
	ft_set_default_env(hash_map);
	return (hash_map);
}

void	ft_free_hash_map(t_hash_table *hash_map)
{
	int			i;
	t_env_node	*current;
	t_env_node	*next;

	if (!hash_map)
		return ;
	i = 0;
	while (i < hash_map->size)
	{
		current = hash_map->items[i];
		while (current)
		{
			next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			current = next;
		}
		i++;
	}
	free(hash_map->items);
	free(hash_map);
}

char	*ft_get_value(t_hash_table *hash_map, char *key)
{
	t_env_node	*current;
	int			index;

	if (!hash_map || !key)
		return (NULL);
	index = ft_hash_djb2((unsigned char *)key) % HASH_SIZE;
	current = hash_map->items[index];
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

t_env_node	*ft_find_env_node(t_hash_table *hash_map, char *key)
{
	t_env_node	*current;
	int			index;

	if (!hash_map || !key)
		return (NULL);
	index = ft_hash_djb2((unsigned char *)key) % HASH_SIZE;
	current = hash_map->items[index];
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
