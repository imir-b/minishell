/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:58:04 by vlad              #+#    #+#             */
/*   Updated: 2026/03/20 00:20:52 by vlad             ###   ########.fr       */
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

# include "libft.h"

# include "data.h"

# include "init.h"
# include "parsing.h"
# include "exec.h"

/* Debug */
void			ft_print_tokens(t_token *tokens);
void			ft_print_ast(t_ast *node, int level);

#endif