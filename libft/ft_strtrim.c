/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 23:03:44 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/17 13:04:22 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*rest;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (ft_strchr(set, s1[i]))
	{
		if (i > len || !s1[i])
			break ;
		i++;
	}
	while (ft_strchr(set, s1[len - 1]))
	{
		if (len == 1)
			break ;
		len--;
	}
	if (len < i)
		return (ft_strdup(""));
	rest = ft_substr(s1, i, len - i);
	return (rest);
}
