/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:10:40 by vbleskin          #+#    #+#             */
/*   Updated: 2026/04/15 23:25:44 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_free_data(t_minishell *data)
{
	int	i;

	i = 0;
	while (data->paths[i])
		free(data->paths[i++]);
	free (data->paths);
	free (data);
	return (NULL);
}
