/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 03:47:53 by vlad              #+#    #+#             */
/*   Updated: 2026/04/15 01:00:04 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_minishell *data, char **args)
{
	int	status;

	(void)data;
	status = g_exit_status;
	if (args && args[0] && args[1])
	{
		status = ft_atoi(args[1]);
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(status);
}
