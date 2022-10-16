/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:47:09 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/16 11:06:52 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO pwd removed path

#include "../includes/minishell.h"

int	ft_pwd(char **args, t_execute *exec, t_env *env)
{
	char	*value;

	(void)env;
	if (args[1])
	{
		ft_putstr_fd("Invalid input\n", 2);
		g_global.exitstauts = 1;
	}
	else
	{
		value = getcwd(NULL, 0);
		leaks_removal(&g_global.g, value);
		if (value)
		{
			ft_putstr_fd(value, exec->output);
			ft_putstr_fd("\n", exec->output);
		}
		else
			ft_putstr_fd("This Directory does not exist\n", 2);
		g_global.exitstauts = 0;
	}
	return (g_global.exitstauts);
}
