/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:56:22 by vlad              #+#    #+#             */
/*   Updated: 2026/04/27 14:32:55 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

int						ft_is_space(char c);

/**
 * Fonction utilitaire qui cherche 'c' dans 'charset' et renvoie 1 si trouve.
 */
int						ft_is_in_charset(char c, char *charset);
char					*ft_extract_word(char *command_line, int *i);
char					*ft_extract_operator(char *command_line, int *i);
t_token					*ft_new_token(char *value, t_token_type type);
void					ft_token_add_back(t_token **tokens, t_token *new_token);
t_token					*ft_token_last(t_token *first);
t_token					*ft_find_operator(t_token *first, t_token_type type1,
							t_token_type type2);
t_token					*ft_tokenizer(char *command_line);
void					*ft_free_tokens(t_token *tokens);
void					ft_break_circle(t_token *first);
void					ft_free_ast(t_ast *self);


t_ast					*ft_create_and_or_node(t_token *current, t_token *first,
							t_minishell *data);
t_ast					*ft_create_pipe_node(t_token *current, t_token *first,
							t_minishell *data);
t_ast					*ft_create_subshell_node(t_token *current,
							t_minishell *data);
t_ast					*ft_create_redir_node(t_token *current, t_token *first,
							t_minishell *data);
t_ast					*ft_create_command_node(t_token *first,
							t_minishell *data);
t_ast					*ft_create_tree(t_token *tokens, t_minishell *data);

int						ft_expand_node(t_ast *node, t_hash_table *hash_map);
void					ft_free_hash_map(t_hash_table *hash_map);
unsigned long			ft_hash_djb2(unsigned char *str);
char					*ft_extract_key(char *str);
int						ft_is_valid_key(char *key);
char					*ft_expand_single_arg(char *arg,
							t_hash_table *hash_map);
char					*ft_get_value(t_hash_table *hash_map, char *key);
t_env_node				*ft_find_env_node(t_hash_table *hash_map, char *key);
void					ft_hash_table_insert(t_hash_table *hash_map,
							char *key, char *value, int export_flag);
char					**ft_word_splitting(char **args);
char					**ft_expand_wildcards(char **args);
t_list					*ft_handle_star(char *arg);
char					**ft_remove_quotes_array(char **args);
char					*ft_remove_quotes(char *arg);
int						ft_process_dollar(char *arg, int *i,
							t_hash_table *hash_map);
int						ft_handle_dollar(char *str, char *ret, int *j,
							t_hash_table *map);
char					*ft_expand_heredoc_line(char *line,
							t_hash_table *hash_map);

int						ft_gather_heredocs(t_ast *node, t_hash_table *hash_map);

#endif