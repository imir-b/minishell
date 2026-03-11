/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:56:28 by vlad              #+#    #+#             */
/*   Updated: 2026/03/09 11:57:59 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef	enum
{
	WORD,
	PIPE,
	REDIR_OUT,
	APPEND,
	REDIR_IN
} TokenType;

typedef struct	s_token
{
	TokenType	type;
	char		*value;
	struct s_token	*next;
} t_token;


#endif