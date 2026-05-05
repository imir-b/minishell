/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:34:33 by vbleskin          #+#    #+#             */
/*   Updated: 2026/04/27 22:24:34 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_matching(char *str, char *pattern, int in_quotes)
{
	if (*str == '\0' && *pattern == '\0')
		return (1);
	if (*pattern == '\'' && in_quotes != '\"')
		return (ft_is_matching(str, pattern +1, in_quotes ^ '\''));
	if (*pattern == '\"' && in_quotes != '\'')
		return (ft_is_matching(str, pattern + 1, in_quotes ^ '\"'));
	if (*pattern == '*')
	{
		if (*str == '\0')
			return (ft_is_matching(str, pattern + 1, in_quotes));
		return (ft_is_matching(str + 1, pattern, in_quotes)
			|| ft_is_matching(str, pattern + 1, in_quotes));
	}
	if (*str == *pattern && *str != '\0')
		return (ft_is_matching(str + 1, pattern + 1, in_quotes));
	return (0);
}

t_list	*ft_handle_star(char *arg)
{
	t_list			*files;
	t_list			*new;
	DIR				*dir;
	struct dirent	*t_dirent;
	char			*path;
	char			*pattern;
	char			*last_slash;

	last_slash = ft_strrchr(arg, '/');
	if (last_slash)
	{
		path = ft_strndup(arg, last_slash - arg);
		pattern = ft_strdup(last_slash + 1);
	}
	else
	{
		path = ft_strdup(".");
		pattern = ft_strdup(arg);
	}
	dir = opendir(path);
	if (!dir)
	{
		free(path);
		free(pattern);
		return (NULL);
	}
	files = NULL;
	t_dirent = readdir(dir);
	while (t_dirent != NULL)
	{
		if (t_dirent->d_name[0] == '.' && pattern[0] != '.')
		{
			t_dirent = readdir(dir);
			continue ;
		}
		if (ft_is_matching(t_dirent->d_name, pattern, 0))
		{
			if (ft_strcmp(path, ".") == 0)
				new = ft_lstnew(ft_strdup(t_dirent->d_name));
			else
				new = ft_lstnew(ft_strjoin(ft_strjoin(ft_strdup(path), "/"), t_dirent->d_name));
			ft_lstadd_back(&files, new);
		}
		t_dirent = readdir(dir);
	}
	free(path);
	free(pattern);
	return (closedir(dir), files);
}
