/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemini <gemini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by gemini            #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_search_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

/**
	* ft_get_cmd_path - Resolves the absolute path of a command.
	* Searches in the directories listed in the PATH environment variable.
	*/
char	*ft_get_cmd_path(char *cmd, t_hash_table *hash_map)
{
	char	*path_env;
	char	**paths;
	char	*res;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = ft_get_value(hash_map, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	res = ft_search_in_paths(paths, cmd);
	ft_free_tab(paths);
	return (res);
}

static int	ft_count_env(t_hash_table *hash_map)
{
	int			count;
	int			i;
	t_env_node	*current;

	count = 0;
	i = 0;
	while (i < HASH_SIZE)
	{
		current = hash_map->items[i];
		while (current)
		{
			if (current->is_exported)
				count++;
			current = current->next;
		}
		i++;
	}
	return (count);
}

static void	ft_fill_env_tab(t_hash_table *hash_map, char **env_tab)
{
	t_env_node	*curr;
	int			i;
	int			j;
	char		*tmp;

	i = 0;
	j = 0;
	while (i < HASH_SIZE)
	{
		curr = hash_map->items[i];
		while (curr)
		{
			if (curr->is_exported)
			{
				tmp = ft_strjoin(curr->key, "=");
				env_tab[j++] = ft_strjoin(tmp, curr->value);
				free(tmp);
			}
			curr = curr->next;
		}
		i++;
	}
	env_tab[j] = NULL;
}

/**
	* ft_get_env_tab - Converts the hash map environment into a char** array.
	* Required for the envp parameter of execve().
	*/
char	**ft_get_env_tab(t_hash_table *hash_map)
{
	char		**env_tab;

	env_tab = malloc(sizeof(char *) * (ft_count_env(hash_map) + 1));
	if (!env_tab)
		return (NULL);
	ft_fill_env_tab(hash_map, env_tab);
	return (env_tab);
}
