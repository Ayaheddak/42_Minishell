/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:11:33 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/09 23:16:06 by het-tale         ###   ########.fr       */
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
	return (1);
}