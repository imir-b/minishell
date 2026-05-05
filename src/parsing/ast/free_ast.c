/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 22:49:50 by vlad              #+#    #+#             */
/*   Updated: 2026/03/27 16:15:37 by vbleskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_cmd_data(t_cmd_data *data)
{
	if (data->args)
		ft_free_array(data->args);
	if (data->path)
		free(data->path);
	free(data);
}

void	free_redir_data(t_redir_data *data)
{
	if (data->file)
		free(data->file);
	free(data);
}

void	ft_free_ast(t_ast *self)
{
	if (!self)
		return ;
	if (self->left)
		ft_free_ast(self->left);
	if (self->right)
		ft_free_ast(self->right);
	if (self->cmd_data)
		free_cmd_data(self->cmd_data);
	if (self->redir_data)
		free_redir_data(self->redir_data);
	free(self);
}
