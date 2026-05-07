/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:00:26 by vlad              #+#    #+#             */
/*   Updated: 2026/04/15 23:17:07 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_heredoc_temp_file_name(void)
{
	char		*temp_file_name;
	char		*temp_pid;
	char		*counter_str;
	static int	counter = 0;

	temp_pid = ft_itoa(getpid());
	counter_str = ft_itoa(counter++);
	temp_file_name = ft_strjoin("/tmp/.heredoc_", temp_pid);
	free(temp_pid);
	temp_pid = temp_file_name;
	temp_file_name = ft_strjoin(temp_pid, counter_str);
	free(temp_pid);
	free(counter_str);
	return (temp_file_name);
}

static int	ft_heredoc_loop(int fd, int saved_stdin, t_redir_data *redir, t_hash_table *map)
{
	char	*line;
	char	*exp;

	while (1)
	{
		line = readline("> ");
		if (g_exit_status == 130)
		{
			dup2(saved_stdin, STDIN_FILENO);
			free(line);
			return (1);
		}
		if (!line || ft_strcmp(line, redir->file) == 0)
			return (free(line), 0);
		if (redir->expand_heredoc)
		{
			exp = ft_expand_heredoc_line(line, map);
			if (!exp)
				return (free(line), perror("expand"), 1);
			free(line);
			line = exp;
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	return (0);
}

int	ft_process_heredoc(t_redir_data *redir_data, t_hash_table *hash_map)
{
	char	*temp_file;
	int		fd;
	int		saved_stdin;
	char	**temp_arr;
	char	**wildcard_exp;

	temp_arr = ft_calloc(2, sizeof(char *));
	temp_arr[0] = ft_strdup(redir_data->file);
	wildcard_exp = ft_expand_wildcards(temp_arr);
	if (wildcard_exp && wildcard_exp[0])
	{
		free(redir_data->file);
		redir_data->file = ft_strdup(wildcard_exp[0]);
	}
	ft_free_tab(wildcard_exp);
	temp_file = ft_get_heredoc_temp_file_name();
	if (!temp_file)
		return (1);
	fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (perror("open"), free(temp_file), 1);
	saved_stdin = dup(STDIN_FILENO);
	ft_setup_signals_heredoc();
	if (ft_heredoc_loop(fd, saved_stdin, redir_data, hash_map))
	{
		close(saved_stdin);
		close(fd);
		unlink(temp_file);
		ft_setup_signals_interactive();
		return (free(temp_file), 1);
	}
	close(saved_stdin);
	close(fd);
	ft_setup_signals_interactive();
	free(redir_data->file);
	redir_data->file = temp_file;
	return (0);
}

int	ft_gather_heredocs(t_ast *node, t_hash_table *hash_map)
{
	if (!node)
		return (0);
	if (node->type == NODE_HEREDOC)
	{
		if (ft_process_heredoc(node->redir_data, hash_map))
			return (1);
	}
	if (ft_gather_heredocs(node->left, hash_map))
		return (1);
	if (ft_gather_heredocs(node->right, hash_map))
		return (1);
	return (0);
}
