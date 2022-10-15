/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 02:15:52 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/15 02:16:31 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	read_from_hrdc(pid_t pd, t_exec *exec_list, int temp_fd)
{
	char	*line;

	line = "";
	if (!pd)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline("> ");
			if (line == NULL)
				exit(0);
			if (!ft_strcmp(exec_list->redir->name, line))
			{
				free(line);
				exit(0);
			}
			write(temp_fd, line, ft_strlen(line));
			free(line);
		}
	}
}

void	here_doc(int *d, t_execute *exec, t_exec *exec_list)
{
	int		temp_fd;
	pid_t	pd;
	int		st;

	temp_fd = open("temp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pd = fork();
	read_from_hrdc(pd, exec_list, temp_fd);
	waitpid(pd, &st, 0);
	if (WIFEXITED(st))
		g_global.exitstauts = WEXITSTATUS(st);
	close(temp_fd);
	exec->input = open("temp_file", O_RDONLY, 0444);
	*d = 0;
}
