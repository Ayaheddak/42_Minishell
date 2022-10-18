/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 02:49:02 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/18 09:10:36 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**init_split(char *s1, char *s2)
{
	char	**split;

	split = (char **)malloc((3) * sizeof(char *));
	leaks_removal(&g_global.g, split);
	split[0] = ft_strdup(s1);
	split[1] = ft_strdup(s2);
	split[2] = NULL;
	return (split);
}

int	nameless_func(char **args, t_env *env_list, int *d, int *i)
{
	char	*st_str;
	char	**split;
	char	*str;

	str = ft_strchr(args[*i], '=');
	if (str)
	{
		st_str = ft_substr(args[*i], 0, ft_strlen(args[*i]) - ft_strlen(str));
		leaks_removal(&g_global.g, st_str);
		split = init_split(st_str, str + 1);
		split = ft_is_contain_equal(env_list, split, d, i);
		if (!split)
			return (1);
		add_back_env(&env_list, create_node(split[0], split[1]));
	}
	return (0);
}

void	loop_through_export(t_env *env_list, char **args, int *d, int i)
{
	while (args[i])
	{
		if (nameless_func(args, env_list, d, &i) == 1)
		{
			i++;
			continue ;
		}
		else if (!ft_strchr(args[i], '='))
		{
			if (is_exist(env_list, args[i]))
			{
				i++;
				continue ;
			}
			if (!ft_isnt_contain_equal(args[i], d, &i))
				continue ;
			add_back_env(&env_list, create_node(args[i], NULL));
		}
		i++;
	}
}
