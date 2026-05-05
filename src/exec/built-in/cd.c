/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 03:47:01 by vlad              #+#    #+#             */
/*   Updated: 2026/04/15 01:00:40 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//entre dans un repo
// cd . et cd .. pour retour en arriere

// chdir() changes the current working directory of the calling process to the directory specified in path.
// On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

void    ft_cd(t_hash_table *hash_map, char *path)
{
    char	*home;
    char	*oldpwd;

    if (path && !*path)
    {
        g_exit_status = 0;
        return ;
    }
    if (!path || ft_strcmp(path, "~") == 0)
    {
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
            g_exit_status = 0;
    }
    else
    {
        oldpwd = ft_get_value(hash_map, "PWD");
        if (chdir(path) != 0)
        {
            perror("cd");
            g_exit_status = 1;
        }
        else
        {
            g_exit_status = 0;
            if (oldpwd)
                ft_hash_table_insert(hash_map, ft_strdup("OLDPWD"), ft_strdup(oldpwd));
            ft_hash_table_insert(hash_map, ft_strdup("PWD"), getcwd(NULL, 0));
        }
    }
}
