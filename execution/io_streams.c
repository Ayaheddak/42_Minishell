/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_streams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:00:58 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/30 12:37:24 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_streams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:00:58 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/30 12:14:29 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc(t_exec *exec, char *name, int *d)
{
	int		temp_fd;
	char	*line;

	temp_fd = open("temp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	*d = 2;
	line = "";
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (!ft_strncmp(name, line, ft_strlen(name))
			&& (ft_strlen(name) + 1) == ft_strlen(line))
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

void	file_exist(int *d, t_exec *exec, t_list *exec_list)
{
	int		type;
	char	*name;

	if (exec_list->file)
	{
		type = exec_list->file->type;
		name = exec_list->file->name;
		if (type == TOKEN_IN)
		{
			exec->infile = open(exec_list->file->name, O_RDONLY, 0444);
			*d = 0;
		}
		else if (type == TOKEN_OUT)
		{
			exec->out_file = open(name, O_CREAT | O_TRUNC | O_RDWR, 0777);
			*d = 1;
		}
		else if (type == TOKEN_APPEND)
		{
			exec->out_file = open(name, O_CREAT | O_APPEND | O_RDWR, 0777);
			*d = 1;
		}
		else if (type == TOKEN_DELIMITER)
			here_doc(exec, name, d);
	}
}

void	input_output(int i, t_exec *exec, t_list *exec_list)
{
	int	d;

	d = -1;
	file_exist(&d, exec, exec_list);
	if (d == -1 || d == 1)
	{
		if (i == 0)
			exec->input = 0;
		else
			exec->input = exec->fd_pipe[(2 * i) - 2];
		if (i == exec->nb_cmd - 1)
			exec->output = 1;
		else
			exec->output = exec->fd_pipe[(2 * i) + 1];
		if (d == 1)
			exec->output = exec->out_file;
	}
	else if (d == 0 || d == 2)
	{
		exec->input = exec->infile;
		if (i == exec->nb_cmd - 1)
			exec->output = 1;
		else
			exec->output = exec->fd_pipe[(2 * i) + 1];
	}
}
