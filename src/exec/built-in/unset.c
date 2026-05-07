/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 03:47:34 by vlad              #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_remove_env_node(t_hash_table *h_m, int idx,
	t_env_node *curr, t_env_node *prev)
{
	if (prev)
		prev->next = curr->next;
	else
		h_m->items[idx] = curr->next;
	free(curr->key);
	free(curr->value);
	free(curr);
}

void	ft_unset(t_hash_table *hash_map, char *key)
{
	int				index;
	t_env_node		*curr;
	t_env_node		*prev;

	if (key == NULL)
		return ;
	index = ft_hash_djb2((unsigned char *)key) % HASH_SIZE;
	curr = hash_map->items[index];
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			ft_remove_env_node(hash_map, index, curr, prev);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
