/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:58:04 by vlad              #+#    #+#             */
/*   Updated: 2026/03/26 12:24:59 by vbleskin         ###   ########.fr       */
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

#endif