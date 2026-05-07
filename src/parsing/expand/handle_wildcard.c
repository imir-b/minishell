/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:34:33 by vbleskin          #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_matching(char *str, char *pattern, int in_quotes)
{
	if (*str == '\0' && *pattern == '\0')
		return (1);
	if (*pattern == '\'' && in_quotes != '\"')
		return (ft_is_matching(str, pattern + 1, in_quotes ^ '\''));
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

static void	ft_add_file_if_match(t_list **files, char *name,
	char *patt, char *path)
{
	t_list	*new;
	char	*joined;

	if (name[0] == '.' && patt[0] != '.')
		return ;
	if (ft_is_matching(name, patt, 0))
	{
		if (ft_strcmp(path, ".") == 0)
			joined = ft_strdup(name);
		else
			joined = ft_super_join(path, name, '/');
		new = ft_lstnew(joined);
		ft_lstadd_back(files, new);
	}
}

static void	ft_split_path_pattern(char *arg, char **path, char **pattern)
{
	char	*last_slash;

	last_slash = ft_strrchr(arg, '/');
	if (last_slash)
	{
		*path = ft_strndup(arg, last_slash - arg);
		*pattern = ft_strdup(last_slash + 1);
	}
	else
	{
		*path = ft_strdup(".");
		*pattern = ft_strdup(arg);
	}
}

t_list	*ft_handle_star(char *arg)
{
	t_list			*files;
	DIR				*dir;
	struct dirent	*t_dirent;
	char			*path;
	char			*pattern;

	ft_split_path_pattern(arg, &path, &pattern);
	dir = opendir(path);
	if (!dir)
		return (free(path), free(pattern), NULL);
	files = NULL;
	t_dirent = readdir(dir);
	while (t_dirent != NULL)
	{
		ft_add_file_if_match(&files, t_dirent->d_name, pattern, path);
		t_dirent = readdir(dir);
	}
	return (free(path), free(pattern), closedir(dir), files);
}
