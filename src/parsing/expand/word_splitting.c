/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:49:58 by vbleskin          #+#    #+#             */
/*   Updated: 2026/04/06 19:10:44 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_words_array(char **strs)
{
	int	i;
	int	j;
	int	total_words;
	int	quotes;

	i = ((total_words = ((quotes = 0))));
	while (strs[i])
	{
		j = 0;
		while (strs[i][j] == ' ')
			j++;
		if (strs[i][0] != '\0')
			total_words++;
		while (strs[i][j])
		{
			if ((strs[i][j] == '\'' || strs[i][j] == '\"')
				&& (!quotes || quotes == strs[i][j]))
				quotes ^= strs[i][j];
			else if (strs[i][j] == ' ' && !quotes && strs[i][j + 1] != ' '
					&& strs[i][j + 1] != '\0')
				total_words++;
			j++;
		}
		i++;
	}
	return (total_words);
}

static int	ft_get_next_word_len(char *str, int start)
{
	int	len;
	int	quotes;

	len = 0;
	quotes = 0;
	while (str[start + len])
	{
		if ((str[start + len] == '\'' || str[start + len] == '\"')
			&& (!quotes || quotes == str[start + len]))
			quotes ^= str[start + len];
		else if (str[start + len] == ' ' && !quotes)
			break ;
		len++;
	}
	return (len);
}

static char	*ft_extract_this(char *str, int *start)
{
	int		len;
	int		i;
	char	*word;

	while (str[*start] == ' ')
		(*start)++;
	len = ft_get_next_word_len(str, *start);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[*start];
		i++;
		(*start)++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_word_splitting(char **args)
{
	int		i;
	int		j;
	char	**dest;
	int		a;

	i = ((a = 0));
	dest = malloc(sizeof(char *) * (ft_count_words_array(args) + 1));
	if (!dest)
		return (NULL);
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			while (args[i][j] == ' ')
				j++;
			if (args[i][j] != '\0')
				dest[a++] = ft_extract_this(args[i], &j);
		}
		i++;
	}
	dest[a] = NULL;
	ft_free_tab(args);
	return (dest);
}
