/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_streams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:00:58 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/16 05:05:43 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	file_utils(int *d, t_execute *exec, t_exec *exec_list, char *name)
{
	if (exec_list->redir->type == TOKEN_DELIMITER)
	{
		here_doc(d, exec, exec_list);
		if (g_global.exitstauts == 1)
		{
			g_global.hd = 0;
			return (1);
		}
	}
	else if (exec_list->redir->type == TOKEN_IN)
	{
		exec->input = open(name, O_RDONLY, 0444);
		*d = 0;
		if (access(name, F_OK) == -1)
			return (1);
	}
	else if (exec_list->redir->type == TOKEN_OUT)
	{
		exec->output = open(name, O_CREAT | O_TRUNC | O_RDWR, 0777);
		*d = 1;
	}
	else if (exec_list->redir->type == TOKEN_APPEND)
	{
		exec->output = open(name, O_CREAT | O_APPEND | O_RDWR, 0777);
		*d = 1;
	}
	return (0);
}

void	file_exist(int *d, t_execute *exec, t_exec *exec_list)
{
	char	*name;

	while (exec_list->redir)
	{
		name = exec_list->redir->name;
		if (file_utils(d, exec, exec_list, name))
			break ;
		exec_list->redir = exec_list->redir->next;
	}
}

void	ft_condition_io(t_execute *exec, int d, int i)
{
	if (d == 0)
	{
		if (exec->output == -2)
		{
			if (i == exec->nb_cmd - 1)
				exec->output = 1;
			else
				exec->output = exec->fd_pipe[(2 * i) + 1];
		}
	}
	else if (d == 1)
	{
		if (exec->input == -2)
		{
			if (i == 0)
				exec->input = 0;
			else
				exec->input = exec->fd_pipe[(2 * i) - 2];
		}
	}
}

void	input_output(int i, t_execute *exec, t_exec *exec_list)
{
	int	d;

	d = -1;
	if (g_global.hd)
	{
		file_exist(&d, exec, exec_list);
		if (d == -1)
		{
			if (i == 0)
				exec->input = 0;
			else
				exec->input = exec->fd_pipe[(2 * i) - 2];
			if (i == exec->nb_cmd - 1)
				exec->output = 1;
			else
				exec->output = exec->fd_pipe[(2 * i) + 1];
		}
		else if (d == 0 || d == 1)
			ft_condition_io(exec, d, i);
	}
}
