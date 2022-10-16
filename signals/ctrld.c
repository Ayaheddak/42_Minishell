/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 22:45:57 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/16 02:04:59 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_d(char *input)
{
	if (!input)
	{
		g_global.exitstauts = 0;
		ft_putstr_fd("exit\n", 1);
		exit(g_global.exitstauts);
	}
}
