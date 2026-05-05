/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:16:06 by vbleskin          #+#    #+#             */
/*   Updated: 2026/04/29 17:50:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ft_handle_sigint - Signal handler for Ctrl-C in interactive mode.
 * Moves the prompt to a new line and redisplays.
 */
void	ft_handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
}

/**
 * ft_handle_sigint_child - Signal handler for Ctrl-C during execution.
 */
void	ft_handle_sigint_child(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", STDOUT_FILENO);
		g_exit_status = 130;
	}
}

/**
 * ft_handle_sigquit_child - Signal handler for Ctrl-\ during execution.
 */
void	ft_handle_sigquit_child(int sig)
{
	if (sig == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", STDOUT_FILENO);
		g_exit_status = 131;
	}
}

/**
 * ft_setup_signals_interactive - Configures signals for the main shell loop.
 */
int	ft_setup_signals_interactive(void)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	return (0);
}

/**
 * ft_setup_signals_exec - Configures signals during command execution.
 * Allows child processes to receive signals normally.
 */
int	ft_setup_signals_exec(void)
{
	signal(SIGINT, ft_handle_sigint_child);
	signal(SIGQUIT, ft_handle_sigquit_child);
	signal(SIGTSTP, SIG_IGN);
	return (0);
}
