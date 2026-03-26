/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 23:50:10 by vlad              #+#    #+#             */
/*   Updated: 2026/03/26 15:23:16 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Fonction pour recuperer la ligne commencant par 'PATH=' dans l'environnement
 * envp.
 */
char	*ft_find_path(char **envp)
{
	const char	*path = "PATH=";

	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (!ft_strncmp(*envp, path, 5))
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

/**
 * Fonction d'initialisation pour minishell
 */
t_minishell	*ft_init_minishell(char **envp)
{
	t_minishell	*data;

	data = malloc(sizeof(t_minishell) * 1);
	data->paths = ft_split(ft_find_path(envp), ':');
	if (!data->paths)
		return (ft_free_data(data));
	data->hash_map = ft_init_hash_map(envp);
	if (!data->hash_map)
		return (ft_free_data(data));
	return (data);
}
