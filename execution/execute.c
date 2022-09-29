/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:03:31 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/29 20:44:25 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_command(t_exec *exec, char **cmd, t_env *env)
{
	char	*right_path;
	char	**str_env;

	if (dup2(exec->input, 0) == -1)
		ft_error("Redirecting input error");
	if (dup2(exec->output, 1) == -1)
		ft_error("Redirecting output error");
	right_path = check_command(cmd[0], env);
	str_env = get_env_array(env);
	if (!right_path)
		exit(1);
	execve(right_path, cmd, str_env);
	free(str_env);
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
		if (access(corr_path->path, F_OK) == 0)
			return (corr_path->path);
		free(corr_path->split[corr_path->j]);
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
	if (access(cmd, F_OK) == 0)
		return (cmd);
	return (get_right_path(env, cmd));
}
