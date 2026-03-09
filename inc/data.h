/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:56:28 by vlad              #+#    #+#             */
/*   Updated: 2026/03/09 14:21:22 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef enum
{
	WORD,
	PIPE,
	REDIR_OUT,
	APPEND,
	REDIR_IN
} TokenType;

typedef struct s_token
{
	TokenType	type;
	char		*value;
	t_token		*next;
}	t_token;

typedef struct s_ast
{

}	t_ast;


#endif