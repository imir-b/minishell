/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:56:28 by vlad              #+#    #+#             */
/*   Updated: 2026/03/25 13:03:26 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef struct s_env_node					t_env_node;

typedef struct s_hash_table					t_hash_table;

typedef enum e_token_type					t_token_type;

typedef struct s_token						t_token;

typedef enum e_node_type					t_node_type;

typedef struct s_cmd_data					t_cmd_data;

typedef struct s_redir_data					t_redir_data;

/**
 * type = type du noeud
 * cmd data = data si le noeud est une commande
 * file = data si le noeud est une redirection
 * right, left = noeuds enfants du noeud actuel
 */
typedef struct s_ast						t_ast;

typedef struct s_minishell					t_minishell;

struct s_env_node
{
	char		*key;
	char		*value;
	t_env_node	*next;
};

struct s_hash_table
{
	t_env_node	**items;
	const int	size;
	int			count;
};

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
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_APPEND,
	NODE_HEREDOC,
	NODE_SUBSHELL
};

struct s_ast
{
	t_node_type		type;
	t_ast			*right;
	t_ast			*left;
	t_cmd_data		*cmd_data;
	t_redir_data	*redir_data;
};

struct s_cmd_data
{
	char	*cmd;
	char	**args;
	char	*path;
};

struct s_redir_data
{
	char	*file;
	int		flags;
};

struct s_minishell
{
	char	**envp;
	char	**paths;
	t_ast	*ast;
};

#endif