/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:56:22 by vlad              #+#    #+#             */
/*   Updated: 2026/03/18 04:20:13 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "data.h"

int			ft_is_space(char c);

/**
 * Fonction utilitaire qui cherche 'c' dans 'charset' et renvoie 1 si trouve.
 */
int			ft_is_in_charset(char c, char *charset);
char		*ft_extract_word(char *command_line, int *i);
char		*ft_extract_operator(char *command_line, int *i);
t_token		*ft_tokenizer(char *command_line);

t_ast		*ft_create_tree(t_token *tokens);

#endif