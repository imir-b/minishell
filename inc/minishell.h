/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:58:04 by username          #+#    #+#             */
/*   Updated: 2026/05/06 13:55:41 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <limits.h>
# include <string.h>

# define HASH_SIZE 256

# include "utils.h"
# include "data.h"
# include "init.h"
# include "parsing.h"
# include "exec.h"

extern int	g_exit_status;

/* Debug */
void	ft_print_tokens(t_token *tokens);
void	ft_print_ast(t_ast *node, int level);

/* Process */
void	ft_print_ascii(void);
void	ft_process_minishell(t_minishell *data);

/* Error */
int		ft_syntax_error(char *token_value);
int		ft_ambiguous_redirect_err(char *str);

/* Free */
void	ft_free_tab(char **tab);

#endif
