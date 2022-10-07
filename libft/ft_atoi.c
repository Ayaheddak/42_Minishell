/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 01:00:54 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/23 22:24:27 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_long(int signe)
{
	if (signe == 1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int					c;
	unsigned long		res;
	int					cmp;

	c = 0;
	res = 0;
	cmp = 1;
	while ((str[c] >= '\t' && str[c] <= '\r') || str[c] == ' ')
		c++;
	if (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			cmp = -1;
		c++;
	}
	while (str[c] >= '0' && str[c] <= '9')
	{
		res = (str[c] - '0') + (res * 10);
		if (res > 9223372036854775807)
			return (check_long(cmp));
		c++;
	}
	return ((int)res * cmp);
}
