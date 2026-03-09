/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:07:03 by vlad              #+#    #+#             */
/*   Updated: 2026/03/09 12:07:34 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	if (ac > 1)
		return (1);
	if (av[1] != "./minishell")
		return (1);
	ft_init_minishell();
	while (1)
	{
		ft_run_minishell();
	}
	return (0);
}
