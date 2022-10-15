/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:03:47 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/15 23:50:22 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO check if local variables added  in env

int	is_valid_arg(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_fd("not valid in this context\n", 2);
		return (0);
	}
	while (str[i])
	{
		if (i == ft_strlen(str) - 1 && str[i] == '+')
			return (1);
		if (!ft_isalnum(str[i]))
		{
			ft_putstr_fd("not valid in this context\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_replaced(t_env *env_list, char *search, char *replace)
{
	t_env	*env_iter;

	env_iter = env_list;
	while (env_iter)
	{
		if (!ft_strcmp(search, env_iter->key))
		{
			env_iter->value = replace;
			return (1);
		}
		env_iter = env_iter->next;
	}
	return (0);
}

int	ft_if_valid(char *str, int *d, int *i)
{
	if (!is_valid_arg(str))
	{
		*d = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

int	ft_export_to_env(t_env *env_list, char **args, t_execute *exec)
{
	int		i;
	int		d;

	i = 1;
	d = 0;
	if (!args[i])
		print_env(env_list, exec, 0);
	loop_through_export(env_list, args, &d, i);
	ft_sort_env(env_list);
	if (!d)
		g_global.exitstauts = 0;
	else
		g_global.exitstauts = 1;
	return (g_global.exitstauts);
}
