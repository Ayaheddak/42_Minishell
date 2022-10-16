/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 20:37:58 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/16 02:27:07 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_call_builtins(t_exec *head, t_env *env_list, t_execute *exec)
{
	if (exec->input == -1)
	{
		perror("infile error");
		g_global.exitstauts = 1;
		return (g_global.exitstauts);
	}
	if (head->args)
	{
		if (!ft_strcmp(head->args[0], "echo"))
			return (ft_echo(head->args, exec));
		else if (!ft_strcmp(head->args[0], "pwd"))
			return (ft_pwd(head->args, exec, env_list));
		else if (!ft_strcmp(head->args[0], "env"))
			return (ft_env(env_list, head->args, exec));
		else if (!ft_strcmp(head->args[0], "cd"))
			return (ft_change_dir(head->args, env_list));
		else if (!ft_strcmp(head->args[0], "unset"))
			return (ft_unset(head->args, env_list));
		else if (!ft_strcmp(head->args[0], "export"))
			return (ft_export_to_env(env_list, head->args, exec));
		else if (!ft_strcmp(head->args[0], "exit"))
			return (ft_exit(head->args));
	}
	return (-1);
}
