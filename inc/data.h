/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:56:28 by vlad              #+#    #+#             */
/*   Updated: 2026/04/09 18:17:15 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

/**
 * --- t_env_node ---
 * Structure pour un item de la table de hachage :
 * - key : cle de la variable
 * - value : valeur de la variable
 * - next : pointeur vers le prochain item en cas de collision
 */
typedef struct s_env_node					t_env_node;

/**
 * --- t_hash_table ---
 * Table de hachage pour stocker les variables d'environnement :
 * - items : table qui stock les variables
 * - size : la taille de la table
 * - count : le nombre de variables qui sont stockes dans la table
 */
typedef struct s_hash_table					t_hash_table;

/**
 * --- t_token_type ---
 * Liste des types de tokens
 */
typedef enum e_token_type					t_token_type;

/**
 * --- t_token ---
 * Liste chainee pour stocker les tokens avant de construire l'ast :
 * - type : le type du token actuel
 * - value : contenu du token
 * - next : pointeur vers le noeud suivant
 * - prev : pointeur vers le noeud precedent
 */
typedef struct s_token						t_token;

/**
 * --- t_node_type ---
 * Liste des types de noeuds pour l'ast
 */
typedef enum e_node_type					t_node_type;

/**
 * --- t_cmd_data ---
 * Structure utilitaire pour les noeuds de type 'commandes' :
 * - cmd : la commande a executer
 * - args : la commande en char ** avec ses arguments
 * - path : le chemin de la commande
 */
typedef struct s_cmd_data					t_cmd_data;

/**
 * --- t_redir_data ---
 * Structure utilitaire pour les noeuds de type 'redirections' :
 * - file : le nom du fichier actuel
 * - flags : les flags a utiliser pour faire open sur le fichier
 */
typedef struct s_redir_data					t_redir_data;

/**
 * --- t_ast ---
 * Arbre pour stocker tous les tokens d'une ligne de commande :
 * - type : type du noeud
 * - cmd data : data pour l'exec si le noeud est une commande
 * - file : data pour l'exec si le noeud est une redirection
 * - right, left : noeuds enfants du noeud actuel (branches)
 */
typedef struct s_ast						t_ast;

/**
 * --- t_minishell ---
 * Structure mere pour minishell :
 * - paths : les chemins des commandes (recupere dans envp)
 * - ast : la data de la ligne de commande
 * - hash_map : table de hachage qui contient les variables d'environnement
 */
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
	int			size;
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
	char			**paths;
	t_ast			*ast;
	t_hash_table	*hash_map;
};

#endif