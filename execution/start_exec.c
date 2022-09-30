/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:41:04 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/30 12:49:07 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(char *str)
{
	perror(str);
	exit(0);
}

t_exec	*init_args(t_list *exec_list)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	exec->nb_cmd = get_size(exec_list);
	exec->fd_pipe = malloc(sizeof(int) * (exec->nb_cmd - 1) * 2);
	exec->child_pid = malloc(sizeof(int) * exec->nb_cmd);
	exec->infile = -1;
	exec->out_file = -1;
	return (exec);
}

void	start_execution(t_list *exec_list, t_env *env)
{
	t_exec	*exec;
	int		i;

	i = 0;
	exec = init_args(exec_list);
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
		exec->child_pid[i] = fork();
		if (exec->child_pid[i] == 0)
		{
			close_pipes(exec, (exec->nb_cmd - 1) * 2);
			execute_command(exec, exec_list->args, env);
		}
		i++;
		exec_list = exec_list->next;
	}
	close_and_free(*exec, exec->nb_cmd);
}
