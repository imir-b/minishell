/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 23:02:45 by vlad              #+#    #+#             */
/*   Updated: 2026/04/15 23:47:18 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", STDOUT_FILENO);
		close(STDIN_FILENO);
	}
}

int	ft_setup_signals_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_handle_sigint_heredoc;
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
