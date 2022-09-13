/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 06:27:29 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/12 02:09:40 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*addnode(void *value)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->data = value;
	newnode->next = NULL;
	return (newnode);
}
//The address of a pointer to the first link of a list.
void add_front(t_list **lst, t_list *new)
{
	new->next=*lst;
	*lst = new;
}

int get_size(t_list *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void add_back(t_list **lst, t_list *new)
{
	t_list *tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return;
	}
	while(tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void print_list(t_list *list)
{
	while (list != NULL)
	{
		printf("%s\n", list->data);
		list = list->next;
	}
}

int main (int ac, char *av[])
{
	t_list *head = addnode("aya");
	t_list *second = addnode("heddak");
	t_list *new = addnode("new");
	head->next = second;
	// second->next = third;
	print_list(head);
	printf("\n\n");
	add_back(&head, new);
	print_list(head);
	// printf("%d\n",get_size(head));
	//add_front(&head, new);
	//printf("data ---> %s", head->data);
	//	print_list(head);
	//t_list *head = NULL;
	//head = mall
}