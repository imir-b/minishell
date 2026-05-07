/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:00:00 by gemini            #+#    #+#             */
/*   Updated: 2026/05/07 11:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_node	*ft_create_env_node(char *key, char *value, int export_flag)
{
	t_env_node	*new;

	new = malloc(sizeof(t_env_node));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->is_exported = export_flag;
	new->next = NULL;
	return (new);
}

static int	ft_update_existing_key(t_env_node *head, char *key,
	char *value, int exp)
{
	t_env_node	*current;

	current = head;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			free(current->value);
			current->value = value;
			if (exp)
				current->is_exported = 1;
			free(key);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	ft_hash_table_insert(t_hash_table *h_m, char *key, char *val, int exp)
{
	int			index;
	t_env_node	*new;
	t_env_node	*current;

	index = ft_hash_djb2((unsigned char *)key) % HASH_SIZE;
	if (h_m->items[index]
		&& ft_update_existing_key(h_m->items[index], key, val, exp))
		return ;
	new = ft_create_env_node(key, val, exp);
	if (!new)
		return ;
	if (!h_m->items[index])
		h_m->items[index] = new;
	else
	{
		current = h_m->items[index];
		while (current->next)
			current = current->next;
		current->next = new;
	}
}
