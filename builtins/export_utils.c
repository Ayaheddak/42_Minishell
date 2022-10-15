/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 01:42:03 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/15 21:54:03 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_join_vars(char **split, t_env *env)
{
	char	*join;
	char	*value;

	if (split[0][ft_strlen(split[0]) - 1] == '+')
	{
		value = get_env_value(env, ft_substr(split[0], 0, ft_strlen(split[0]) - 1));
		join = freejoin(value, split[1]);
		return (join);
	}
	return (NULL);
}

char	**ft_is_contain_equal(t_env *env_list, char **args, int *d, int *i)
{
	char	**split;
	char	*substr;
	char	*join;

	split = ft_split(args[*i], '=');
	if (!split[1])
		split[1] = "";
	if (!split[0])
	{
		ft_putstr_fd("`=': not a valid identifier\n", 2);
		*d = 1;
		(*i)++;
		return (NULL);
	}
	join = ft_join_vars(split, env_list);
	if (join)
	{
		substr = ft_substr(split[0], 0, ft_strlen(split[0]) - 1);
		if (is_replaced(env_list, substr, join))
		{
			(*i)++;
			return (NULL);
		}
		else
		{
			add_back_env(&env_list, create_node(substr, join));
			(*i)++;
			return (NULL);
		}
			
	}
	if (is_replaced(env_list, split[0], split[1]))
	{
		(*i)++;
		return (NULL);
	}
	if (ft_if_valid(split[0], d, i))
		return (NULL);
	return (split);
}

void	loop_through_export(t_env *env_list, char **args, int *d, int i)
{
	char	**split;

	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			split = ft_is_contain_equal(env_list, args, d, &i);
			if (!split)
			{
				continue ;
				i++;
			}
			add_back_env(&env_list, create_node(split[0], split[1]));
		}
		else
		{
			if (!is_valid_arg(args[i]))
			{
				*d = 1;
				i++;
				continue ;
			}
			add_back_env(&env_list, create_node(args[i], NULL));
		}
		i++;
	}
}
