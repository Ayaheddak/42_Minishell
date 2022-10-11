/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrlc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 00:01:46 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/11 02:34:43 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c(int signum)
{
	(void)signum;
	g_global.exitstauts = 130;
	rl_on_new_line ();
	// rl_replace_line("minishell", 0);
	rl_redisplay ();
}