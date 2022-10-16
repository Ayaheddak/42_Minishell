/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:05:25 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/16 11:10:11 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipes(t_execute *exec, int n)
{
	int	j;

	j = 0;
	while (j < n)
	{
		if (exec->fd_pipe[j] != exec->input
			&& exec->fd_pipe[j] != exec->output)
			close(exec->fd_pipe[j]);
		j++;
	}
}

void	close_and_free(t_execute exec, int n)
{
	int	i;

	i = 0;
	if (exec.input)
		close(exec.input);
	if (exec.output != 1)
		close(exec.output);
	unlink("temp_file");
	while (i < (n - 1) * 2)
	{
		close(exec.fd_pipe[i]);
		i++;
	}
	i = -1;
	if (exec.created_process)
	{
		waitpid(exec.child_pid[n - 1], &(exec.status), 0);
		while (++i < n - 1)
			waitpid(-1, NULL, 0);
		if (WIFEXITED(exec.status))
			g_global.exitstauts = WEXITSTATUS(exec.status);
		if (WIFSIGNALED(exec.status))
			g_global.exitstauts = WTERMSIG(exec.status) + 128;
	}
	if (exec.nb_cmd > 1)
	{
		free(exec.child_pid);
		free(exec.fd_pipe);
	}
}
