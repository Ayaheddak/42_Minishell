/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 08:13:38 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/14 00:36:52 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

char	*freejoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	j = (ft_strlen(s1) + ft_strlen(s2) + 1);//
	rest = (char *)malloc(sizeof(char) * j);
	if (!rest)
		return (NULL);
	j = 0;
	while (s1[i] != '\0')
		rest[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		rest[j++] = s2[i++];
	rest[j] = '\0';
	// free(s1);
	// free(s2);
	return (rest);
}

void	addback(t_token **head, void *value, void *type, int split)
{
	t_token	*new;
	t_token	*temp;

	new = malloc(sizeof(t_token));
	new->value = value;
	new->split = split;
	new->type = *(int *)type;
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
