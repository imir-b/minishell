/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 03:47:44 by vlad              #+#    #+#             */
/*   Updated: 2026/03/28 16:49:59 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_item(t_env_node *item, int fd)
{
	if (item->key && item->value)
	{
		ft_putstr_fd(item->key, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(item->value, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	ft_env(t_hash_table *hash_map)
{
	int			index;
	t_env_node	*current_item;

	index = 0;
	while (index < HASH_SIZE)
	{
		current_item = hash_map->items[index];
		while (current_item)
		{
			ft_print_item(current_item, STDOUT_FILENO);
			current_item = current_item->next;
		}
		index++;
	}
}
