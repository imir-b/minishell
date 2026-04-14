/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 03:47:34 by vlad              #+#    #+#             */
/*   Updated: 2026/04/15 01:01:30 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_hash_table *hash_map, char *key)
{
	unsigned long	hash;
	int				index;
	t_env_node		*current;
	t_env_node		*prev;

	if (key == NULL)
		return ;
	hash = ft_hash_djb2((unsigned char *)key);
	index = hash % HASH_SIZE;
	current = hash_map->items[index];
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				hash_map->items[index] = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
