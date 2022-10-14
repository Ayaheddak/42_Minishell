/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_streams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:00:58 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/14 05:22:01 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc(t_exec *exec_list, int	*temp_fd)
{
	char	*line;

	*temp_fd = open("temp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	line = "";
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			exit(1);
		if (!ft_strncmp(exec_list->redir->name, line, ft_strlen(exec_list->redir->name))
			&& (ft_strlen(exec_list->redir->name) + 1) == ft_strlen(line))
		{
			free(line);
			exit(1);
		}
		write(*temp_fd, line, ft_strlen(line));
		free(line);
	}
}

void	file_exist(int *d, t_execute *exec, t_exec *exec_list)
{
	pid_t	pd;
	int status;
	int		temp_fd;

	while (exec_list->redir)
	{
		if (exec_list->redir->type == TOKEN_DELIMITER)
		{
			pd = fork();
			if (!pd)
			{
				ctrl_c(NULL);
				here_doc(exec_list, &temp_fd);
			}
			waitpid(pd, &status, 0);
			close(temp_fd);
			exec->input = open("temp_file", O_RDONLY, 0444);
			*d = 0;
		}
		else if (exec_list->redir->type == TOKEN_IN)
		{
			exec->input = open(exec_list->redir->name, O_RDONLY, 0444);
			*d = 0;
		}
		else if (exec_list->redir->type == TOKEN_OUT)
		{
			exec->output = open(exec_list->redir->name, O_CREAT | O_TRUNC | O_RDWR, 0777);
			*d = 1;
		}
		else if (exec_list->redir->type == TOKEN_APPEND)
		{
			exec->output = open(exec_list->redir->name, O_CREAT | O_APPEND | O_RDWR, 0777);
			*d = 1;
		}
		exec_list->redir = exec_list->redir->next;
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
		if (exec->input == -2) // <<end cat > out
		{
			if (i == 0)
				exec->input = 0;
			else
				exec->input = exec->fd_pipe[(2 * i) - 2];
		}
	}
}
