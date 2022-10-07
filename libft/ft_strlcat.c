/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:55:00 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/23 22:22:47 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t		i;
	size_t		lendst;
	size_t		lensrc;

	i = 0;
	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (dstsize <= lendst)
		return (lensrc + dstsize);
	while (i < dstsize - 1 - lendst && src[i])
	{
		dst[lendst + i] = src[i];
		i++;
	}
	dst[lendst + i] = '\0';
	return (lendst + lensrc);
}
