/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:56:22 by vlad              #+#    #+#             */
/*   Updated: 2026/03/09 11:59:43 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "data.h"

int			ft_is_space(char c);
int			ft_is_special_char(char c);
char		*ft_extract_word(char *command_line, int *i);
char		*ft_extract_operator(char *command_line, int *i);
t_token		*ft_tokenizer(char *command_line);

#endif