/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 23:50:10 by vlad              #+#    #+#             */
/*   Updated: 2026/03/09 14:20:27 by vbleskin         ###   ########.fr       */
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

void	*ft_parse_tokens(t_token *tokens);

void	ft_run_minishell()
{
	t_token	*tokens;
	t_ast	*ast;
	char	*command_line;
	void	*ast;

	command_line = NULL;

	if (command_line)
		free(command_line);
	command_line = get_next_line(STDIN_FILENO);
	tokens = ft_tokenizer(command_line);
	ast = ft_parse_tokens(tokens);
	(void)ast; // Prevent unused variable warning
}
