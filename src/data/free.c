/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:10:40 by vbleskin          #+#    #+#             */
/*   Updated: 2026/03/18 04:10:52 by vbleskin         ###   ########.fr       */
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
