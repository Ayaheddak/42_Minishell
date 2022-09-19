/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:48:22 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/19 20:52:37 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_list *env_list, t_list *list)
{
	t_list  *env_iter;
    char    *join;

    env_iter = env_list;
	if (list->next)
		printf("Sorry we said no options no arguments!\n");
	else
	{
		while (env_iter)
		{
            join = ft_strjoin(env_iter->id, "=");
            join = ft_strjoin(join, env_iter->data);
			printf("%s\n", join);
			env_iter = env_iter->next;
		}
	}	
}