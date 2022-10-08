/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_streams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:00:58 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/08 11:57:31 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    file_exist(int  *d, t_execute *exec, t_exec *exec_list)
{
    if (exec_list->redir)
	{
		if (exec_list->redir->type == TOKEN_IN)
		{
			exec->infile = open(exec_list->redir->name, O_RDONLY, 0444);
			*d = 0;
		}
		else if (exec_list->redir->type == TOKEN_OUT)
		{
			exec->out_file = open(exec_list->redir->name, O_CREAT | O_TRUNC | O_RDWR, 0777);
			*d = 1;
		}
		else if (exec_list->redir->type == TOKEN_APPEND)
		{
			exec->out_file = open(exec_list->redir->name, O_CREAT | O_APPEND | O_RDWR, 0777);
			*d = 1;
		}
	}
}

void	input_output(int i, t_execute *exec, t_exec *exec_list)
{
	int	d;

	d = -1;
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
	else if (d == 0)
	{
		exec->input = exec->infile;
		if (i == exec->nb_cmd - 1)
			exec->output = 1;
		else
			exec->output = exec->fd_pipe[(2 * i) + 1];
	}
	else if (d == 1)
	{
		if (i == 0)
			exec->input = 0;
		else
			exec->input = exec->fd_pipe[(2 * i) - 2];
		exec->output = exec->out_file;
	}	
}