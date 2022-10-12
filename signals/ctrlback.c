/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrlback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:20:07 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/12 08:07:31 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrlback(int d)
{
	if (d == 0)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, SIG_DFL);
}
