/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 03:47:53 by vlad              #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_numeric(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_exit_error(char *arg, t_minishell *data)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	if (data)
		ft_free_data(data);
	exit(2);
}

void	ft_exit(t_minishell *data, char **args)
{
	int	status;

	status = g_exit_status;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (args && args[1])
	{
		if (!ft_is_numeric(args[1]))
			ft_exit_error(args[1], data);
		if (args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO);
			g_exit_status = 1;
			return ;
		}
		status = ft_atoi(args[1]) % 256;
	}
	if (data)
		ft_free_data(data);
	exit(status);
}
