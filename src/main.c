/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:07:03 by vlad              #+#    #+#             */
/*   Updated: 2026/03/18 04:36:44 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	*data;

	if (ac > 1)
		return (1);
	(void)av;
	data = ft_init_minishell(envp);
	ft_setup_signals();
	ft_process_minishell(data);
	return (0);
}
