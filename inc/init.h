/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:18:56 by vlad              #+#    #+#             */
/*   Updated: 2026/04/07 14:40:20 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "minishell.h"

t_minishell		*ft_init_minishell(char **envp);
void			ft_process_minishell(t_minishell *data);
t_hash_table	*ft_init_hash_map(char **envp);

void			ft_setup_signals(void);

void			*ft_free_data(t_minishell *data);

#endif