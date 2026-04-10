/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:51:19 by username          #+#    #+#             */
/*   Updated: 2026/04/10 16:34:16 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_has_unquoted_star(char *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && (!quotes || quotes == str[i]))
			quotes ^= str[i];
		else if (str[i] == '*' && !quotes)
			return (1);
		i++;
	}
	return (0);
}

void	ft_expand_single_arg_wildcard(t_list **args_lst, char *arg)
{
	t_list	*expanded_files;
	char	*clean_pattern;

	if (ft_has_unquoted_star(arg))
	{
		clean_pattern = ft_remove_quotes(arg);
		expanded_files = ft_handle_star(clean_pattern);
		if (expanded_files)
			ft_lstadd_back(args_lst, expanded_files);
		else
			ft_lstadd_back(args_lst, ft_lstnew(ft_strdup(arg)));
		free(clean_pattern);
	}
	else
		ft_lstadd_back(args_lst, ft_lstnew(ft_strdup(arg)));
}

int	ft_lstdup(char **dest, t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		dest[i] = ft_strdup((const char *)lst->content);
		if (!dest[i])
			return (1);
		i++;
		lst = lst->next;
	}
	dest[i] = NULL;
	return (0);
}

int	ft_check_for_wildcard(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_has_unquoted_star(args[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**ft_expand_wildcards(char **args)
{
	char	**dest;
	t_list	*args_lst;
	int		i;
	int		has_wildcard;

	has_wildcard = ft_check_for_wildcard(args);
	if (!has_wildcard)
		return (args);
	i = 0;
	args_lst = NULL;
	while (args[i])
	{
		ft_expand_single_arg_wildcard(&args_lst, args[i]);
		i++;
	}
	dest = malloc(sizeof(char *) * (ft_lstsize(args_lst) + 1));
	if (!dest)
		return (NULL);
	if (ft_lstdup(dest, args_lst))
		return (free(dest), NULL);
	ft_lstclear(&args_lst, free);
	ft_free_tab(args);
	return (dest);
}
