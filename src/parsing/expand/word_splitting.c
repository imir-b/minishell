/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:49:58 by vbleskin          #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_in_str(char *s)
{
	int	j;
	int	count;
	int	quotes;

	j = 0;
	count = 0;
	quotes = 0;
	while (s[j] == ' ')
		j++;
	if (s[j] != '\0')
		count++;
	while (s[j])
	{
		if ((s[j] == '\x01' || s[j] == '\x02') && (!quotes || quotes == s[j]))
			quotes ^= s[j];
		else if (s[j] == ' ' && !quotes && s[j + 1] != ' ' && s[j + 1] != '\0')
			count++;
		j++;
	}
	return (count);
}

int	ft_count_words_array(char **strs)
{
	int	i;
	int	total_words;

	i = 0;
	total_words = 0;
	while (strs[i])
	{
		total_words += ft_count_in_str(strs[i]);
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
		if ((str[start + len] == '\x01' || str[start + len] == '\x02')
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

	i = 0;
	a = 0;
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
	return (ft_free_tab(args), dest);
}
