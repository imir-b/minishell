/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:16:06 by vbleskin          #+#    #+#             */
/*   Updated: 2026/04/15 23:15:32 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	ft_setup_signals_interactive(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_handle_sigint;
	if (sigemptyset(&sa.sa_mask) == -1)
		return (1);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (1);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (1);
	return (0);
}

int	ft_setup_signals_exec(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	if (sigemptyset(&sa.sa_mask) == -1)
		return (1);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (1);
	return (0);
}
