/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrlc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 00:01:46 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/12 08:07:35 by het-tale         ###   ########.fr       */
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
}

void	ctrl_c(void)
{
	signal(SIGINT, ctl_handler);
}
