/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:34:33 by vbleskin          #+#    #+#             */
/*   Updated: 2026/04/10 16:34:47 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	ft_is_matching(char *str, char *pattern)
{
	if (*str == '\0' && *pattern == '\0')
		return (1);
	if (*str == *pattern && *str != '\0')
		return (ft_is_matching(str + 1, pattern + 1));
	if (*pattern == '*')
	{
		if (*str == '\0')
			return (ft_is_matching(str, pattern + 1));
		return (ft_is_matching(str + 1, pattern)
			|| ft_is_matching(str, pattern + 1));
	}
	return (0);
}

t_list	*ft_handle_star(char *arg)
{
	t_list			*files;
	t_list			*new;
	DIR				*dir;
	struct dirent	*t_dirent;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	files = NULL;
	t_dirent = readdir(dir);
	while (t_dirent != NULL)
	{
		if (t_dirent->d_name[0] == '.' && arg[0] != '.')
		{
			t_dirent = readdir(dir);
			continue ;
		}
		if (ft_is_matching(t_dirent->d_name, arg))
		{
			new = ft_lstnew(ft_strdup(t_dirent->d_name));
			ft_lstadd_back(&files, new);
		}
		t_dirent = readdir(dir);
	}
	return (closedir(dir), files);
}
