/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:51:19 by username          #+#    #+#             */
/*   Updated: 2026/04/09 23:34:19 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_wildcard(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '*' && args[i][j + 1] == '.' && args[i][j + 2])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

t_list	*ft_handle_star(char *wildcard)
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
		if (ft_is_matching(t_dirent->d_name, wildcard))
		{
			new = ft_lstnew(ft_strdup(t_dirent->d_name));
			ft_lstadd_back(&files, new);
		}
		t_dirent = readdir(dir);
	}
	closedir(dir);
	return (files);
}

int	ft_expand_single_arg_wildcard(t_list **args_lst, char *arg)
{
	int		j;
	char	*star;
	t_list	*expanded_files;

	j = 0;
	star = NULL;
	while (arg[j])
	{
		star = ft_strchr(star, '*');
		if (star)
		{
			expanded_files = ft_handle_star(star);
			if (expanded_files)
				ft_lstadd_back(args_lst, expanded_files);
			else
				ft_lstadd_back(args_lst, ft_lstnew(ft_strdup(arg)));
		}
		else
			ft_lstadd_back(args_lst, ft_lstnew(ft_strdup(arg)));
		j++;
	}
}

char	**ft_expand_wildcards(char **args)
{
	char	**dest;
	t_list	*args_lst;
	int		i;

	if (!ft_is_wildcard(args))
		return (args);
	i = 0;
	while (args[i])
	{
		ft_expand_single_arg_wildcard(&args_lst, args[i]);
		i++;
	}
	dest = malloc(sizeof(char *) * (ft_lstsize(args_lst) + 1));
	if (!dest)
		return (NULL);
	return (dest);
}
