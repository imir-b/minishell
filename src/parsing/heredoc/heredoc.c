/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:00:26 by vlad              #+#    #+#             */
/*   Updated: 2026/04/15 01:08:36 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_process_heredoc(char *delimiter, t_hash_table *hash_map)
{
	char	*line;
	char	*temp_file_name;
	int		fd;

	temp_file_name = ft_strjoin("/tmp/.heredoc_", ft_itoa(getpid()));
	if (!temp_file_name)
		return (1);
	fd = open(temp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (perror("open"), free(temp_file_name), 1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	close(fd);
	ft_hash_table_insert(hash_map, temp_file_name, temp_file_name);
	return (0);
}

int	ft_gather_heredocs(t_ast *node, t_hash_table *hash_map)
{
	if (!node)
		return (0);
	if (node->type == NODE_HEREDOC)
	{
		if (ft_process_heredoc(node->redir_data->file, hash_map))
			return (1);
	}
	if (ft_gather_heredocs(node->left, hash_map))
		return (1);
	if (ft_gather_heredocs(node->right, hash_map))
		return (1);
	return (0);
}
