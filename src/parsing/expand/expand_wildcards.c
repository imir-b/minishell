/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:51:19 by username          #+#    #+#             */
/*   Updated: 2026/04/09 17:34:40 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wildcard_len(char **args, struct dirent *t_dirent)
{
	int	len;

	return (len);
}

int	ft_is_wildcard(char **arg)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i])
	{
		j = 0;
		while (arg[i][j])
		{
			if (arg[i][j] == '*' && arg[i][j + 1] == '.' && arg[i][j + 2])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

char	**ft_expand_wildcards(char **args)
{
	DIR				*current;
	struct dirent	*t_dirent;
	char			**dest;

	if (!ft_is_wildcard(args))
		return (args);
	current = opendir(".");
	if (!current)
		return (NULL);
	t_dirent = readdir(current);
	if (!t_dirent)
		return (closedir(current), NULL);
	dest = malloc(sizeof(char *) * ft_wildcard_len(args, t_dirent));
	if (!dest)
		return (closedir(current), NULL);
	closedir(current);
	return (dest);
}
