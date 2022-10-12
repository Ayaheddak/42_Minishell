/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:11:33 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/10 21:35:08 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*remove_list(t_env **env_list, t_env *remove)
{
	t_env	*temp;

	temp = *env_list;
	if (remove == temp)
		*env_list = temp->next;
	else
	{
		while (temp)
		{
			if(temp->next == remove)
			{
				temp->next = remove->next;
				free(remove);
				break;
			}
			temp = temp->next;
		}
	}
	return (*env_list);
}

int	ft_unset(char **args, t_env *env_iter)
{
	int	i;
	t_env	*env;

	i = 1;
	if (args[i] && !is_valid_arg(args[i]))
	{
		g_global.exitstauts = 1;
		return (g_global.exitstauts);
	}
	while (args[i])
    {
		env = env_iter;
        while (env)
        {
            if (!ft_strcmp(args[i], env->key))
                env_iter = remove_list(&env_iter, env);
            env = env->next;
        }
		i++;
    }
	g_global.exitstauts = 0;
	return (g_global.exitstauts);
}