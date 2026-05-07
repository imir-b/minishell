/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 03:47:12 by vlad              #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_cwd_dynamic(void)
{
	size_t	size;
	char	*buf;

	size = 1024;
	buf = malloc(size);
	while (buf && !getcwd(buf, size))
	{
		if (errno != ERANGE)
		{
			free(buf);
			return (NULL);
		}
		free(buf);
		size *= 2;
		buf = malloc(size);
	}
	return (buf);
}

void	ft_pwd(void)
{
	char	*buf;

	buf = ft_get_cwd_dynamic();
	if (buf)
	{
		ft_putstr_fd(buf, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		free(buf);
	}
}
