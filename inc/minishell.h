/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:58:04 by vlad              #+#    #+#             */
/*   Updated: 2026/04/06 19:08:04 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>

# include "libft.h"

# include "data.h"

# define HASH_SIZE 256

# include "init.h"
# include "parsing.h"
# include "exec.h"

/* Debug */
void			ft_print_tokens(t_token *tokens);
void			ft_print_ast(t_ast *node, int level);

/* Error */
int				ft_syntax_error(char *token_value);
int				ft_ambiguous_redirect_err(char *str);

/* Free */
void			ft_free_tab(char **tab);


#endif