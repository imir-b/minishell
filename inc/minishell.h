/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:58:04 by vlad              #+#    #+#             */
/*   Updated: 2026/03/18 04:21:34 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "data.h"

# include "parsing.h"
# include "libft.h"

t_minishell		*ft_init_minishell(char **envp);
void			ft_process_minishell(t_minishell *data);

void			ft_setup_signals(void);

void			*ft_free_data(t_minishell *data);

#endif