/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:56:28 by vlad              #+#    #+#             */
/*   Updated: 2026/03/18 04:28:39 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef enum e_token_type					t_token_type;

typedef struct s_token						t_token;

typedef enum e_node_type					t_node_type;

typedef struct s_cmd_data					t_cmd_data;

/**
 * type = type du noeud
 * cmd data = data si le noeud est une commande
 * file = data si le noeud est une redirection
 * right, left = noeuds enfants du noeud actuel
 */
typedef struct s_ast						t_ast;

typedef struct s_minishell					t_minishell;

enum e_token_type
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_APPEND,
	TOK_HEREDOC,
	TOK_AND,
	TOK_OR,
	TOK_L_PAREN,
	TOK_R_PAREN
};

struct s_token
{
	t_token_type	type;
	char			*value;
	t_token			*next;
	t_token			*prev;
};

enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
};

struct s_cmd_data
{
	char	*cmd;
	char	**args;
	char	*path;
};

struct s_ast
{
	t_node_type	*type;
	t_cmd_data	*cmd_data;
	char		*file;
	t_ast		*right;
	t_ast		*left;
};

struct s_minishell
{
	char	**envp;
	char	**paths;
};

#endif