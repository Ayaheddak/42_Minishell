/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_streams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:00:58 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/29 23:41:13 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    file_exist(int  *d, t_exec *exec, t_list *exec_list)
{
	int		temp_fd;
	char	*line;

    if (exec_list->file)
	{
		if (exec_list->file->type == TOKEN_IN)
		{
			exec->infile = open(exec_list->file->name, O_RDONLY, 0444);
			*d = 0;
		}
		else if (exec_list->file->type == TOKEN_OUT)
		{
			exec->out_file = open(exec_list->file->name, O_CREAT | O_TRUNC | O_RDWR, 0777);
			*d = 1;
		}
		else if (exec_list->file->type == TOKEN_APPEND)
		{
			exec->out_file = open(exec_list->file->name, O_CREAT | O_APPEND | O_RDWR, 0777);
			*d = 1;
		}
		else if (exec_list->file->type == TOKEN_APPEND)
		{
			exec->out_file = open(exec_list->file->name, O_CREAT | O_APPEND | O_RDWR, 0777);
			*d = 1;
		}
		else if (exec_list->file->type == TOKEN_DELIMITER)
		{
			temp_fd = open("temp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
			*d = 2;
			line = "";
			while (1)
			{
				line = get_next_line(0);
				if (line == NULL)
					break ;
				if (!ft_strncmp(exec_list->file->name, line, ft_strlen(exec_list->file->name))
					&& (ft_strlen(exec_list->file->name) + 1) == ft_strlen(line))
				{
					free(line);
					break ;
				}
				write(temp_fd, line, ft_strlen(line));
				free(line);
			}
			close(temp_fd);
			exec->infile = open("temp_file", O_RDONLY, 0444);
		}
	}
}

void	input_output(int i, t_exec *exec, t_list *exec_list)
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
	else if (d == 2)
	{
		exec->input = exec->infile;
		if (i == exec->nb_cmd - 1)
			exec->output = 1;
		else
			exec->output = exec->fd_pipe[(2 * i) + 1];
	}
}