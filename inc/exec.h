/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:17:07 by vlad              #+#    #+#             */
/*   Updated: 2026/03/20 00:22:17 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

void    ft_execute(t_minishell *data);
int		ft_exec_command(t_ast *node, t_minishell *data);
int		ft_exec_node(t_ast *node, t_minishell *data);
int		ft_exec_pipe(t_ast *node, t_minishell *data);
int		ft_exec_redir(t_ast *node, t_minishell *data);
int		ft_exec_logical(t_ast *node, t_minishell *data);
int		ft_exec_subshell(t_ast *node, t_minishell *data);
char	*ft_get_cmd_path(char *cmd, t_hash_table *hash_map);
char	**ft_get_env_tab(t_hash_table *hash_map);

/* Built-ins */
void    ft_cd(t_hash_table *hash_map, char *path);
void    ft_echo(char **args);
void    ft_env(t_hash_table *hash_map);
void    ft_exit(t_minishell *data, char **args);
void    ft_export(t_hash_table *hash_map, char **args);
void    ft_pwd(void);
void    ft_unset(t_hash_table *hash_map, char *key);

#endif