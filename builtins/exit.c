/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:13:00 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/17 01:56:13 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	if_arguments(char **args)
{
	int	d;

	ft_putstr_fd("exit\n", 1);
	if (args[2])
	{
		ft_putstr_fd("too many arguments\n", 2);
		g_global.exitstauts = 1;
	}
	else
	{
		if (ft_is_string(args[1]))
		{
			g_global.exitstauts = 255;
			ft_putstr_fd("numeric argument required\n", 2);
		}
		else
		{
			d = ft_atoi(args[1]);
			g_global.exitstauts = d;
		}
		exit(g_global.exitstauts);
	}
}

int	ft_exit(char **args)
{
	if (!args[1])
	{
		g_global.exitstauts = 0;
		ft_putstr_fd("exit\n", 1);
		exit(g_global.exitstauts);
	}
	else
		if_arguments(args);
	return (g_global.exitstauts);
}
