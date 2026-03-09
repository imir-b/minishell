/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 23:50:10 by vlad              #+#    #+#             */
/*   Updated: 2026/03/09 12:07:30 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Affiche le bandeau ascii au lancement de minishell
 */
void	ft_print_ascii()
{
	
}

/**
 * Fonction d'initialisation pour minishell
 */
void	ft_init_minishell()
{
	ft_print_ascii();
}

void	ft_run_minishell()
{
	t_token	*tokens;
	char	*command_line;

	if (command_line)
		free(command_line);
	command_line = get_next_line(STD_OUT);
	tokens = ft_tokenizer(command_line);
	ast = ft_parse_tokens(tokens);
}
