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
	int	i;

	status = g_exit_status;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (args && args[1])
	{
		i = 0;
		if (args[1][i] == '+' || args[1][i] == '-')
			i++;
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
				ft_putstr_fd(args[1], STDERR_FILENO);
				ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
				status = 2;
				if (data)
					ft_free_data(data);
				exit(status);
			}
			i++;
		}
		if (args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			g_exit_status = 1;
			return ;
		}
		status = ft_atoi(args[1]) % 256;
	}
	if (data)
		ft_free_data(data);
	exit(status);
}
