/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 01:42:03 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/18 04:20:00 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_join_vars(char **split, t_env *env)
{
	char	*join;
	char	*value;
	char	*substr;

	if (split[0][ft_strlen(split[0]) - 1] == '+')
	{
		substr = ft_substr(split[0], 0, ft_strlen(split[0]) - 1);
		value = get_env_value(env, substr);
		join = freejoin(value, split[1]);
		return (join);
	}
	return (NULL);
}

int	ft_is_equal_utils(char **split, char *join, int *i, t_env *env_list)
{
	char	*substr;

	substr = ft_substr(split[0], 0, ft_strlen(split[0]) - 1);
	if (is_replaced(env_list, substr, join))
	{
		(*i)++;
		return (0);
	}
	else
	{
		add_back_env(&env_list, create_node(substr, join));
		(*i)++;
		return (0);
	}
	return (1);
}

char	**ft_is_contain_equal(t_env *env_list, char **args, int *d, int *i)
{
	char	*join;

	if (!ft_strcmp(args[0], ""))
	{
		ft_putstr_fd("`=': not a valid identifier\n", 2);
		*d = 1;
		(*i)++;
		return (NULL);
	}
	join = ft_join_vars(args, env_list);
	if (join && !ft_is_equal_utils(args, join, i, env_list))
		return (NULL);
	if (is_replaced(env_list, args[0], args[1]))
	{
		(*i)++;
		return (NULL);
	}
	if (ft_if_valid(args[0], d, i))
		return (NULL);
	return (args);
}

int	ft_isnt_contain_equal(char *args, int *d, int *i)
{
	if (!is_valid_arg(args))
	{
		*d = 1;
		(*i)++;
		return (0);
	}
	return (1);
}

int	is_exist(t_env *env, char *key)
{
	if (!key)
		return (0);
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (1);
		env = env->next;
	}
	return (0);
}
