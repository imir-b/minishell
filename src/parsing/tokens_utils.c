/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:45:51 by vlad              #+#    #+#             */
/*   Updated: 2026/03/20 14:45:53 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_break_circle(t_token *first)
{
	first->prev->next = NULL;
	first->prev = NULL;
}

void	*ft_free_tokens(t_token *tokens)
{
	t_token *tmp;

	if (!tokens)
		return (NULL);
	if (tokens->prev)
		ft_break_circle(tokens);
	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
	return (NULL);
}
