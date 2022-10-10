/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 20:37:58 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/10 02:17:34 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_call_builtins(t_exec *head, t_env *env_list, t_execute *exec)
{
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
        else if (!ft_strcmp(head->args[0], "unset"))
            return (ft_unset(head->args, env_list));
        else if (!ft_strcmp(head->args[0], "export"))
            return (ft_export_to_env(env_list, head->args));
        // else if (ft_strncmp(head->data, "exit", ft_strlen(head->data)) == 0)
        //     ft_exit();
    }
	return (-1);
}