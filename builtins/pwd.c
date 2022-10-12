/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:47:09 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/12 07:24:11 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(char **args, t_execute *exec)
{
	char	*value;

	if (args[1])
	{
		ft_putstr_fd("Invalid input\n", 2);
		g_global.exitstauts = 1;
	}
	else
	{
		value = getcwd(NULL, 100);
		if (value)
		{
			ft_putstr_fd(value, exec->output);
			ft_putstr_fd("\n", exec->output);
		}
		g_global.exitstauts = 0;
	}
	return (g_global.exitstauts);
}
