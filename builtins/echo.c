/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:01:59 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/09 15:45:20 by het-tale         ###   ########.fr       */
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
				d = 1;
			i++;
		}
	}
	if (d < 0 || d == 1)
		return (0);
	return (1);
}

int	ft_echo(char **args)
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
			printf("%s", args[i]);
			d = 1;
		}
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!args[1] || (args[1] && !valid_option(args[1])))
		printf("\n");
	return (1);
}
