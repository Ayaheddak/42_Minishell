/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrlc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 00:01:46 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/14 23:46:07 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctl_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
	if (errno == EINTR)
	{
		rl_on_new_line ();
		rl_replace_line("", 0);
		rl_redisplay ();
	}
	g_global.exitstauts = 1;
}

int	ctrl_c(char **line)
{
	signal(SIGINT, ctl_handler);
	if (line)
		*line = NULL;
	return (1);
}
