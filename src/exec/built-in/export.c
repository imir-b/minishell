/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 03:47:21 by vlad              #+#    #+#             */
/*   Updated: 2026/04/15 00:59:16 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_hash_table_insert(t_hash_table *hash_map, char *key, char *value)
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
	if (!hash_map->items[index])
		hash_map->items[index] = new;
	else
	{
		current = hash_map->items[index];
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	ft_export(t_hash_table *hash_map, char *key, char *value)
{
	if (key == NULL || value == NULL)
		return ;
	ft_hash_table_insert(hash_map, key, value);
}