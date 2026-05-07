/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:07:03 by vlad              #+#    #+#             */
/*   Updated: 2026/05/08 01:03:40 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	ft_print_ascii(void)
{
	printf("\033[35m       .             *             \
		 .              *\033[0m\n");
	printf("\033[35m  *           ☾             .       \
		        *              .\033[0m\n");
	printf("\033[33m      _____ _    _ ______ ______  ___\
		__ _    _ ______ _      _\033[0m\n");
	printf("\033[33m     |_   _| |  | |  ____|  ____|/ ___\
		_| |  | |  ____| |    | |\033[0m\n");
	printf("\033[33m       | | | |  | | |__  | |__  | (___ |\
		 |__| | |__  | |    | |\033[0m\n");
	printf("\033[33m       | | | |  | |  __| |  __|  \\___ \\|\
		  __  |  __| | |    | |\033[0m\n");
	printf("\033[33m       | | | |__| | |    | |     ____) | | \
		 | | |____| |____| |____\033[0m\n");
	printf("\033[33m       |_|  \\____/|_|    |_|    |_____/|_|\
		  |_|______|______|______|\033[0m\n");
	printf("\033[31m  .                                      \
		                                *\033[0m\n");
	printf("\033[31m        *             ☭             .     \
		        ☭              *\033[0m\n\n");
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*data;

	if (ac > 1)
		return (1);
	(void)av;
	data = ft_init_minishell(envp);
	ft_setup_signals_interactive();
	ft_print_ascii();
	ft_process_minishell(data);
	ft_free_data(data);
	return (0);
}
