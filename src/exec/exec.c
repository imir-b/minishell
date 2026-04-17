/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:16:22 by vlad              #+#    #+#             */
/*   Updated: 2026/04/16 02:43:45 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	ft_exec_node(t_ast *node, t_minishell *data)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (ft_exec_command(node, data));
	// ajouter les autres types de noeuds (pipe, redirections, etc.)
	return (0);
}

void	ft_execute(t_minishell *data)
{
	ft_setup_signals_exec();
	ft_exec_node(data->ast, data);
	ft_setup_signals_interactive();
}
