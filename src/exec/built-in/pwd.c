/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 03:47:12 by vlad              #+#    #+#             */
/*   Updated: 2026/03/28 16:49:01 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	size_t	size;
	char	*ret;
	char	*buffer;

	size = 1024;
	buffer = malloc(sizeof(char) * size);
	if (!buffer)
		return ;
	ret = getcwd(buffer, size);
	while (ret == NULL)
	{
		if (errno == ERANGE)
		{
			free(buffer);
			size *= 2;
			buffer = malloc(sizeof(char) * size);
			if (!buffer)
				return ;
			ret = getcwd(buffer, size);
		}
		else
		{
			free(buffer);
			return ;
		}
	}
	ft_putstr_fd(buffer, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(buffer);
}
