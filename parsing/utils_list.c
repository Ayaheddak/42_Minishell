/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 08:13:38 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/06 23:39:58 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*freejoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*rest;
	size_t	count;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	count = ft_strlen(s1) + ft_strlen(s2) + 1;
	rest = (char *)malloc(sizeof(char) * count);
	if (!rest)
		return (NULL);
	while (s1[i] != '\0')
		rest[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		rest[j++] = s2[i++];
	rest[j] = '\0';
	free(s1);
	free(s2);
	return (rest);
}

void addback(t_token **head, void *value, void *type)
{
    t_token *new;
	t_token *temp;

	new = malloc(sizeof(t_token));
    new->value = value;
	new->type = *(int *)type;
    new->next = NULL;
    if(*head == NULL)
	{
        *head = new;
        return;
    }
	temp = *head;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = new;
}

void	addredirection(t_redir **head, int type, char *file)
{
	t_redir *tmp;
	t_redir *new;

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
	while(tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void print_redir(t_redir *redir)
{
	int i;
	
	i = 0;
    while(redir != NULL)
    {
		printf("------------- Node numbre %d  = -------------\n" , i);
        printf("ur name of file = %s\n", redir->name);
		printf("ur type = %d\n",redir->type); 
		redir = redir->next;
		i++;
    }
}

