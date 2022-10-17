/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 08:13:38 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/17 04:34:02 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*freejoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	j = (ft_strlen(s1) + ft_strlen(s2) + 1);
	rest = (char *)malloc(sizeof(char) * j);
	leaks_removal(&g_global.g, rest);
	if (!rest)
		return (NULL);
	j = 0;
	while (s1[i] != '\0')
		rest[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		rest[j++] = s2[i++];
	rest[j] = '\0';
	free(s1);
	return (rest);
}

void	addback(t_token **head, void *value, void *type, int split)
{
	t_token	*new;
	t_token	*temp;

	new = malloc(sizeof(t_token));
	leaks_removal(&g_global.g, new);
	new->value = value;
	new->split = split;
	new->e_type = *(int *)type;
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void	addredirection(t_redir **head, int type, char *file)
{
	t_redir	*tmp;
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	leaks_removal(&g_global.g, new);
	new->name = file;
	new->type = type;
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

char	*conv_char(char c)
{
	char	*res;

	res = malloc(sizeof(char) * 2);
	if (!res)
		return (NULL);
	res[0] = c;
	res[1] = '\0';
	return (res);
}

int	needs_splitting(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
