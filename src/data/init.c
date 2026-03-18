/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 23:50:10 by vlad              #+#    #+#             */
/*   Updated: 2026/03/18 04:10:32 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Affiche le bandeau ascii au lancement de minishell
 */
void	ft_print_ascii(void)
{
	write(1, "MINISHELL\n", 10);
}

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
	data->envp = envp;
	data->paths = ft_split(ft_find_path(envp), ':');
	if (!data->paths)
		return (ft_free_data(data));
	ft_print_ascii();
	return (data);
}
