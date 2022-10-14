/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_streams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:00:58 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/14 23:40:26 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc(int *d, t_execute *exec, t_exec *exec_list)
{
	int		temp_fd;
	char	*line;
	pid_t	pd;
	int	st;

	temp_fd = open("temp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	line = "";
	pd = fork();
	if (!pd)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline("> ");
			if (line == NULL)
				exit(0);
			if (!ft_strncmp(exec_list->redir->name, line, ft_strlen(exec_list->redir->name))
				&& (ft_strlen(exec_list->redir->name)) == ft_strlen(line))
			{
				free(line);
				exit(0);
			}
			write(temp_fd, line, ft_strlen(line));
			free(line);
		}
	}
	waitpid(pd, &st, 0);
	if (WIFEXITED(st))
		g_global.exitstauts = WEXITSTATUS(st);
	close(temp_fd);
	exec->input = open("temp_file", O_RDONLY, 0444);
	*d = 0;
}

void	file_exist(int *d, t_execute *exec, t_exec *exec_list)
{
	while (exec_list->redir)
	{
		if (exec_list->redir->type == TOKEN_DELIMITER)
		{
			here_doc(d, exec, exec_list);
			if (g_global.exitstauts == 1)
			{
				g_global.hd = 0;
				break ;
			}
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
}
