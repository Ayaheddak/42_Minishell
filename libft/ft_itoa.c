/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:53:15 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/23 22:24:01 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	ft_check(int n)
{
	int				i;
	unsigned int	nb;

	i = 0;
	nb = n;
	if (n < 0)
	{
		nb = -n;
		i++;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	unsigned int	nb;

	nb = n;
	i = ft_check(n);
	str = malloc(sizeof(char) * (i + 1));
	if (str == 0)
		return (NULL);
	str[i] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		nb = -n;
	}
	i--;
	while (nb >= 10)
	{
		str[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	if (nb <= 9)
	str[i] = nb + '0';
	return (str);
}
