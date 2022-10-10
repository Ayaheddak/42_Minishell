/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:03:47 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/10 20:58:12 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_') || (str[i] == '=')))
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

	i = 1;
	if (args[i] && !is_valid_arg(args[i]))
		return (0);
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
				return (0);
			}
			if (is_replaced(env_list, split[0], split[1]))
				break ;
			add_back_env(&env_list, create_node(split[0], split[1]));
		}
		else
			add_back_env(&env_list, create_node(args[i], NULL));
		i++;
	}
	return (1);
}