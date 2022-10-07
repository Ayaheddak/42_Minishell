// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   start_exec.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/09/29 14:41:04 by het-tale          #+#    #+#             */
// /*   Updated: 2022/10/07 21:26:37 by het-tale         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

// void	ft_error(char *str)
// {
// 	perror(str);
// 	exit(0);
// }

// void	start_execution(t_exec *exec_list, t_env *env)
// {
// 	t_execute	*exec;
// 	int	i;

// 	exec = malloc(sizeof(t_execute));
// 	exec->nb_cmd = ft_lstsize(exec_list);
// 	i = 0;
// 	exec->fd_pipe = malloc(sizeof(int) * (exec->nb_cmd - 1) * 2);
// 	exec->child_pid = malloc(sizeof(int) * exec->nb_cmd);
// 	exec->infile = -1;
// 	exec->out_file = -1;
// 	while (i < exec->nb_cmd - 1)
// 	{	
// 		if (pipe(exec->fd_pipe + 2 * i) == -1)
// 			ft_error("Pipe");
// 		i++;
// 	}
// 	i = 0;
// 	while (exec_list)
// 	{
// 		input_output(i, exec, exec_list);
// 		exec->child_pid[i] = fork();
// 		if (exec->child_pid[i] == 0)
// 		{
// 			close_pipes(exec, (exec->nb_cmd - 1) * 2);
// 			execute_command(exec, exec_list->args, env);
// 		}
// 		i++;
// 		exec_list = exec_list->next;
// 	}
// 	close_and_free(*exec, exec->nb_cmd);
// }