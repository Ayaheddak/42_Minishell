/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:01:59 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/18 00:57:13 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_option(char *str)
{
	size_t	len;
	size_t	i;
	int		d;

	len = ft_strlen(str);
	i = 1;
	d = -1;
	if (str[0] == '-')
	{
		while (i < len)
		{
			d = 0;
			if (str[i] != 'n')
			{
				d = 1;
				break ;
			}
			i++;
		}
	}
	if (d < 0 || d == 1)
		return (0);
	return (1);
}

int	ft_echo(char **args, t_execute *exec)
{
	int	i;
	int	d;

	i = 1;
	d = 0;
	while (args[i])
	{
		if (valid_option(args[i]) && !d)
		{
			i++;
			continue ;
		}
		if (args[i])
		{
			ft_putstr_fd(args[i], exec->output);
			d = 1;
		}
		if (args[i + 1])
			ft_putstr_fd(" ", exec->output);
		i++;
	}
	if (!args[1] || (args[1] && !valid_option(args[1])))
		ft_putstr_fd("\n", exec->output);
	g_global.exitstauts = 0;
	return (g_global.exitstauts);
}
