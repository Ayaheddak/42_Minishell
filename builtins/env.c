/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:48:22 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/18 04:17:15 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_key_value(char *key, char *value, int d)
{
	char	*join;

	join = ft_strjoin(key, "=");
	if (!d)
		join = ft_strjoin(join, value);
	else
	{
		join = ft_strjoin(join, "\"");
		join = ft_strjoin(join, value);
		join = ft_strjoin(join, "\"");
	}
	return (join);
}

int	ft_env_condition(t_env *env, t_execute *exec, char *join)
{
	ft_putstr_fd("declare -x ", exec->output);
	if (!env->value)
	{
		ft_putstr_fd(env->key, exec->output);
		ft_putstr_fd("\n", exec->output);
		return (1);
	}
	else if (!ft_strcmp(env->value, ""))
	{
		join = join_key_value(env->key, env->value, 1);
		ft_putstr_fd(join, exec->output);
		ft_putstr_fd("\"\"", exec->output);
		ft_putstr_fd("\n", exec->output);
		return (1);
	}
	return (0);
}

int	env_conditions(t_env *env, int d, char **join, t_execute *exec)
{
	if (d == 1)
	{
		if (!env->value)
			return (1);
		*join = join_key_value(env->key, env->value, 0);
	}
	if (!d)
	{
		if (ft_env_condition(env, exec, *join))
			return (1);
		*join = join_key_value(env->key, env->value, 1);
	}
	return (0);
}

void	print_env(t_env *env, t_execute *exec, int d)
{
	char	*join;

	join = NULL;
	while (env)
	{
		if (env_conditions(env, d, &join, exec))
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd(join, exec->output);
		ft_putstr_fd("\n", exec->output);
		env = env->next;
	}
}

int	ft_env(t_env *env, char **args, t_execute *exec)
{
	int		i;

	i = 1;
	if (args[i])
	{
		g_global.exitstauts = 1;
		ft_putstr_fd("Invalid input\n", 2);
	}
	else
	{
		print_env(env, exec, 1);
		g_global.exitstauts = 0;
	}
	return (g_global.exitstauts);
}
