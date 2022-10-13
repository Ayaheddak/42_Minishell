/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:03:31 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/13 22:28:24 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_command(t_execute *exec, t_exec *exec_list, t_env *env)
{
	char	*right_path;
	char	**str_env;

	if (exec->input == -1)
		ft_error("input");
	if (exec->output == -1)
		ft_error("output");
	if (exec->input != 0 && dup2(exec->input, 0) == -1)
		ft_error("Redirecting input error");
	if (exec->output != 1 && dup2(exec->output, 1) == -1)
		ft_error("Redirecting output error");
	right_path = check_command(exec_list->args[0], env);
	str_env = get_env_array(env);
	if (!right_path)
		ft_error("Error command");
	execve(right_path, exec_list->args, str_env);
}

char	*get_right_path_utils(t_path *corr_path, char *cmd, t_env *env)
{
	corr_path->d = 1;
	corr_path->split = ft_split(env->value, ':');
	corr_path->j = 0;
	while (corr_path->split[corr_path->j])
	{
		corr_path->path = ft_strjoin(corr_path->split[corr_path->j], "/");
		corr_path->path = ft_strjoin(corr_path->path, cmd);
		if (access(corr_path->path, F_OK | X_OK) == 0)
			return (corr_path->path);
		corr_path->j++;
	}
	return (NULL);
}

char	*get_right_path(t_env *env, char *cmd)
{
	t_path	corr_path;

	corr_path.i = 0;
	corr_path.len = 0;
	corr_path.d = 0;
	corr_path.path = NULL;
	while (env)
	{
		if (!ft_strcmp(env->key, "PATH"))
			corr_path.path = get_right_path_utils(&corr_path, cmd, env);
		if (corr_path.d == 1)
			break ;
		env = env->next;
	}
	return (corr_path.path);
}

char	*check_command(char *cmd, t_env *env)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	return (get_right_path(env, cmd));
}
