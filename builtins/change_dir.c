/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:29:48 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/17 23:06:07 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*change_pwd(t_env *env_list, char *key)
{
	t_env	*env;

	env = env_list;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			env->value = getcwd(NULL, 0);
			leaks_removal(&g_global.g, env->value);
			break ;
		}
		env = env->next;
	}
	return (env_list);
}

void	if_no_arguments(t_env *env, int *change)
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

void	ft_conditions(char **args, t_env *env, int *change)
{
	int		i;
	char	*buf;

	i = 1;
	if (args[i])
	{
		buf = getcwd(NULL, 0);
		leaks_removal(&g_global.g, buf);
		if (buf)
			env = change_pwd(env, "OLDPWD");
		*change = chdir(args[i]);
		if (buf)
			env = change_pwd(env, "PWD");
	}
	else
		if_no_arguments(env, change);
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
