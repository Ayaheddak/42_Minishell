/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 08:13:38 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/17 12:08:37 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list	*addnode(void *data)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->data = data;
	newnode->next = NULL;
	return (newnode);
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
		printf("value ---->%s\n", list-data);
		//printf("value ---->%s\n", list->value);
		list = list->next;
	}
}

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

// t_list	*addnode(void *value, void *value)
// {
// 	t_list	*newnode;

// 	newnode = (t_list *)malloc(sizeof(t_list));
// 	if (!newnode)
// 		return (NULL);
// 	newnode->value = value;
// 	newnode->value = value;
// 	newnode->next = NULL;
// 	return (newnode);
// }
// t_list *get_env(char	**env)//i think it can help u f export
// {
// 	int	i;
// 	int j;
// 	char **split;
// 	t_list *head;

// 	i = 0;
// 	head = NULL;
// 	while (env[i])
// 	{
// 		j = 0;
// 		split = ft_split(env[i],'=');
// 		while(split[j])
// 			j++;
// 		add_back(&head,addnode(split[j-2],split[j-1]));
// 		i++;
// 	}
// 	return (head);
// }

// int main (int ac, char *av[])
// {
// 	t_list *head = addnode("aya");
// 	t_list *second = addnode("heddak");
// 	t_list *new = addnode("new");
// 	head->next = second;
// 	// second->next = third;
// 	print_list(head);
// 	printf("\n\n");
// 	add_back(&head, new);
// 	print_list(head);
// 	// printf("%d\n",get_size(head));
// 	//add_front(&head, new);
// 	//printf("data ---> %s", head->data);
// 	//	print_list(head);
// 	//t_list *head = NULL;
// 	//head = mall
// }