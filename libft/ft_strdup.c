/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:43:39 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/18 01:04:11 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup(char *s1)
{
	unsigned int	len;
	unsigned int	i;
	char			*p;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	p = (char *)malloc((len + 1) * sizeof(char));
	leaks_removal(&g_global.g, p);
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
