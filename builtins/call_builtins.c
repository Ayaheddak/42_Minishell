/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 20:37:58 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/09 22:42:43 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_call_builtins(t_exec *head, t_env *env_list, t_execute *exec)
{
	(void)env_list;
	if (head->args)
	{
		if (!ft_strcmp(head->args[0], "echo"))
			return (ft_echo(head->args, exec));
        else if (!ft_strcmp(head->args[0], "pwd"))
            return (ft_pwd(head->args, env_list, exec));
        else if (!ft_strcmp(head->args[0], "env"))
            return (ft_env(env_list, head->args, exec));
        else if (!ft_strcmp(head->args[0], "cd"))
            return (ft_change_dir(head->args, env_list));
        // else if (ft_strncmp(head->data, "unset", ft_strlen(head->data)) == 0)
        //     ft_unset(head, env_list);
        // else if (ft_strncmp(head->data, "export", ft_strlen(head->data)) == 0)
        //     ft_export(env_list, head);
        // else if (ft_strncmp(head->data, "exit", ft_strlen(head->data)) == 0)
        //     ft_exit();
    }
	return (-1);
}