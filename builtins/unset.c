/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:11:33 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/19 19:18:41 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list  *remove_list(t_list **env_list, t_list *remove)
{
    t_list  *temp;

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

t_list  *ft_unset(t_list *list, t_list *env_list)
{
	t_list  *temp;
    t_list  *env_iter;

	temp = list->next;
	while (temp)
    {
        env_iter = env_list;
        while (env_iter)
        {
            if (!ft_strncmp(env_iter->id, temp->data, ft_strlen(temp->data)))
                env_list = remove_list(&env_list, env_iter);
            env_iter = env_iter->next;
        }
        temp = temp->next;
    }
	return (env_list);
}