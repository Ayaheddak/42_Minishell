/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:03:47 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/14 23:29:42 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//to edit
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

int	ft_export_to_env(t_env *env_list, char **args, t_execute *exec)
{
	char	**split;
	int		i;
	int		d;

	i = 1;
	d = 0;
	if (!args[i])
		print_env(env_list, exec, 0);
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			split = ft_split(args[i], '=');
			if(!split[1])
				split[1] = "";
			if(!split[0])
			{
				ft_putstr_fd("`=': not a valid identifier\n", 2);
				d = 1;
				i++;
				continue ;
			}
			if (is_replaced(env_list, split[0], split[1]))
			{
				i++;
				continue ;
			}
			if (!is_valid_arg(split[0]))
			{
				d = 1;
				i++;
				continue ;
			}
			add_back_env(&env_list, create_node(split[0], split[1]));
		}
		else
		{
			if (!is_valid_arg(args[i]))
			{
				d = 1;
				i++;
				continue ;
			}
			add_back_env(&env_list, create_node(args[i], NULL));
		}
		i++;
	}
	if (!d)
		g_global.exitstauts = 0;
	else
		g_global.exitstauts = 1;
	return (g_global.exitstauts);
}