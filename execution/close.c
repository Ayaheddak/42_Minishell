/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:05:25 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/12 07:22:22 by het-tale         ###   ########.fr       */
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
	if (exec.infile != -2)
		close(exec.infile);
	if (exec.out_file != -2)
		close(exec.out_file);
	unlink("temp_file");
	while (i < (n - 1) * 2)
	{
		close(exec.fd_pipe[i]);
		i++;
	}
	if (exec.nb_cmd > 1)
	{
		i = -1;
		while (++i < n)
			waitpid(-1, &(exec.status), 0);
		if (WIFEXITED(exec.status))
			g_global.exitstauts = WEXITSTATUS(exec.status);
		free(exec.child_pid);
		free(exec.fd_pipe);
	}
}
