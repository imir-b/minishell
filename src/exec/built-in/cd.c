/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 03:47:01 by vlad              #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_update_pwd(t_hash_table *hash_map)
{
	char	*oldpwd;
	char	*cwd;

	oldpwd = ft_get_value(hash_map, "PWD");
	if (oldpwd)
		ft_hash_table_insert(hash_map, ft_strdup("OLDPWD"),
			ft_strdup(oldpwd), 0);
	cwd = getcwd(NULL, 0);
	if (cwd)
		ft_hash_table_insert(hash_map, ft_strdup("PWD"), cwd, 0);
}

static void	ft_cd_home(t_hash_table *hash_map)
{
	char	*home;

	home = ft_get_value(hash_map, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		g_exit_status = 1;
	}
	else if (chdir(home) != 0)
	{
		perror("cd");
		g_exit_status = 1;
	}
	else
	{
		g_exit_status = 0;
		ft_update_pwd(hash_map);
	}
}

void	ft_cd(t_hash_table *hash_map, char *path)
{
	if (path && !*path)
	{
		g_exit_status = 0;
		return ;
	}
	if (!path || ft_strcmp(path, "~") == 0)
		ft_cd_home(hash_map);
	else
	{
		if (chdir(path) != 0)
		{
			perror("cd");
			g_exit_status = 1;
		}
		else
		{
			g_exit_status = 0;
			ft_update_pwd(hash_map);
		}
	}
}
