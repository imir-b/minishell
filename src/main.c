/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:07:03 by vlad              #+#    #+#             */
/*   Updated: 2026/04/10 21:52:41 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_minishell	*data;

	if (ac > 1)
		return (1);
	(void)av;
	data = ft_init_minishell(envp);
	// ft_setup_signals();
	// ft_print_ascii();
	ft_process_minishell(data);
	return (0);
}
