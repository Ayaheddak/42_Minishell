/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 20:37:58 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/19 21:41:25 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_call_builtins(t_list *head, t_list *env_list)
{  
    if (head)
    {
        if (ft_strncmp(head->data, "echo", ft_strlen(head->data)) == 0)
		ft_echo(head);
        else if (ft_strncmp(head->data, "pwd", ft_strlen(head->data)) == 0)
            ft_pwd(env_list, head);
        else if (ft_strncmp(head->data, "env", ft_strlen(head->data)) == 0)
            ft_env(env_list, head);
        else if (ft_strncmp(head->data, "cd", ft_strlen(head->data)) == 0)
            ft_change_dir(head, env_list);
        else if (ft_strncmp(head->data, "unset", ft_strlen(head->data)) == 0)
            ft_unset(head, env_list);
        else if (ft_strncmp(head->data, "export", ft_strlen(head->data)) == 0)
            ft_export(env_list, head);
        else if (ft_strncmp(head->data, "exit", ft_strlen(head->data)) == 0)
            ft_exit();
    }
}