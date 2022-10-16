/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:35:29 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/16 04:23:36 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_count_parts(char const *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	if (*str == '\0')
		return (0);
	while (str[i] == sep)
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == sep && str[i + 1] != sep && str[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static	int	word_length(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static	char	**ft_free(int j, char **str)
{
	while (j >= 0)
	{
		free(str[j]);
		j--;
	}
	free(str);
	return (NULL);
}

static char	**fill_array(char **str, char const *s, char c)
{
	int	i;
	int	j;
	int	word_l;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			word_l = word_length(&s[i], c);
			str[j] = ft_substr(s, i, word_l);
			if (!str[j])
				return (ft_free(j, str));
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	str[j] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		count;

	if (!s)
		return (0);
	count = ft_count_parts(s, c);
	str = (char **)malloc((count + 1) * sizeof(char *));
	leaks_removal(&g_global.g, str);
	if (!str)
		return (0);
	str = fill_array(str, s, c);
	return (str);
}
