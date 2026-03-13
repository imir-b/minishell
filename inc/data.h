/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:56:28 by vlad              #+#    #+#             */
/*   Updated: 2026/03/13 22:24:29 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	AND,
	OR,
	L_PAREN,
	R_PAREN
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_token			*next;
	t_token			*prev;
}	t_token;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}	t_node_type;

typedef struct s_cmd_data
{
	char	*cmd;
}	t_cmd_data;

typedef struct s_ast
{
	t_node_type	*type;
	t_cmd_data	*cmd_data;
	t_ast		*right;
	t_ast		*left;
}	t_ast;


#endif