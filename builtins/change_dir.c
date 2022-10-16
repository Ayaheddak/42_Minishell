/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:29:48 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/16 00:45:22 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO print error msg when directory is deleted 
/**
 * * TODO: test this case : << here cat file1 > f2 | grep l > f2 
 */

t_env	*change_pwd(t_env *env_list, char *key)
{
	t_env	*env;

	env = env_list;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			env->value = getcwd(NULL, 0);
			break ;
		}
		env = env->next;
	}
	return (env_list);
}

void	ft_conditions(char **args, t_env *env, int *change)
{
	int	i;

	i = 1;
	if (args[i] && getcwd(NULL, 0))
	{
		env = change_pwd(env, "OLDPWD");
		*change = chdir(args[i]);
		env = change_pwd(env, "PWD");
	}
	else
	{
		env = change_pwd(env, "OLDPWD");
		while (env)
		{
			if (!ft_strcmp(env->key, "HOME"))
			{
				*change = chdir(env->value);
				break ;
			}
			env = env->next;
		}
		env = change_pwd(env, "PWD");
	}
}

int	ft_change_dir(char **args, t_env *env)
{
	int	change;

	change = 0;
	ft_conditions(args, env, &change);
	if (change == -1)
	{
		perror("cd");
		g_global.exitstauts = 1;
	}
	else
		g_global.exitstauts = 0;
	return (g_global.exitstauts);
}
