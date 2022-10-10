/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:41:04 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/10 21:40:30 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(char *str)
{
	perror(str);
	g_global.exitstauts = 1;
	exit(g_global.exitstauts);
}

void	start_execution(t_exec *exec_list, t_env *env)
{
	t_execute	*exec;
	int			i;
	int			stdin;
	int			stdout;

	exec = malloc(sizeof(t_execute));
	exec->nb_cmd = get_size(exec_list);
	stdin = 0;
	stdout = 1;
	i = 0;
	exec->fd_pipe = malloc(sizeof(int) * (exec->nb_cmd - 1) * 2);
	exec->child_pid = malloc(sizeof(int) * exec->nb_cmd);
	exec->infile = -1;
	exec->out_file = -1;
	while (i < exec->nb_cmd - 1)
	{	
		if (pipe(exec->fd_pipe + 2 * i) == -1)
			ft_error("Pipe");
		i++;
	}
	i = 0;
	while (exec_list)
	{
		input_output(i, exec, exec_list);
		if (exec->nb_cmd == 1 && ft_call_builtins(exec_list, env, exec) != -1)
			break ;
		exec->child_pid[i] = fork();
		if (exec->child_pid[i] == 0)
		{
			close_pipes(exec, (exec->nb_cmd - 1) * 2);
			execute_command(exec, exec_list, env);
		}
		i++;
		exec_list = exec_list->next;
	}
	close_and_free(*exec, exec->nb_cmd);
}
