/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:41:04 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/17 05:31:21 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(char *str)
{
	perror(str);
	g_global.exitstauts = 1;
	exit(g_global.exitstauts);
}

void	init_args(t_exec *exec_list, t_execute *exec)
{
	int	i;

	i = 0;
	exec->input = -2;
	exec->output = -2;
	exec->nb_cmd = get_size(exec_list);
	exec->fd_pipe = malloc(sizeof(int) * (exec->nb_cmd - 1) * 2);
	leaks_removal(&g_global.g, exec->fd_pipe);
	exec->child_pid = malloc(sizeof(int) * exec->nb_cmd);
	leaks_removal(&g_global.g, exec->child_pid);
	while (i < exec->nb_cmd - 1)
	{	
		if (pipe(exec->fd_pipe + 2 * i) == -1)
			ft_error("Pipe");
		i++;
	}
}

void	ft_close_inside(t_execute *exec)
{
	if (exec->input != 0)
		close(exec->input);
	if (exec->output != 1)
		close(exec->output);
	exec->input = -2;
	exec->output = -2;
}

int	exec_builtins(t_exec *exec_list, t_execute *exec, t_env *env)
{
	if (!g_global.hd)
		return (0);
	if (exec->nb_cmd == 1 && ft_call_builtins(exec_list, env, exec) != -1)
	{
		exec->created_process = 0;
		return (0);
	}
	return (1);
}

void	start_execution(t_exec *exec_list, t_env *env)
{
	t_execute	*exec;
	int			i;

	i = 0;
	exec = malloc(sizeof(t_execute));
	leaks_removal(&g_global.g, exec);
	init_args(exec_list, exec);
	while (exec_list)
	{
		input_output(i, exec, exec_list);
		if (!exec_builtins(exec_list, exec, env))
			break ;
		exec->child_pid[i] = fork();
		exec->created_process = 1;
		if (exec->child_pid[i] == 0)
		{
			signals(1);
			close_pipes(exec, (exec->nb_cmd - 1) * 2);
			execute_command(exec, exec_list, env);
		}
		i++;
		ft_close_inside(exec);
		exec_list = exec_list->next;
	}
	close_and_free(*exec, exec->nb_cmd);
}
