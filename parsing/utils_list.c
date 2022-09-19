/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 08:13:38 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/19 22:10:09 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*addnode(void *id, void *data)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->data = data;
	newnode->id = id;
	newnode->next = NULL;
	return (newnode);
}

void add_back(t_list **lst, t_list *new)
{
	t_list *tmp;

	tmp = *lst;
	if (tmp == NULL)
		*lst = new;
	else
	{
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void print_list(t_list *list)
{
	int i;

	i = 0;
	while (list != NULL)
	{
		printf("------------- Node numbre %d  = -------------\n" , i);
		printf("ur id = %d\n",*(int*)list->id);
		printf("ur value = %s\n", (char*)list->data);
		i++;
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

// t_list  *get_list(int argc, char *argv[])
// {
//     t_list *list;
// 	t_list	*temp;
//     int     i;

//     i = 1;
// 	list = NULL;
//     while (i < argc && argv[i])
//     {
//         temp = addnode((char *)argv[i]);
//         add_back(&list, temp);
//         i++;
//     }
//     return (list);
// }

t_list	*get_env(char *env[])
{
	int		i;
	char	**split;
	t_list	*head;

	i = 0;
	head = NULL;
	while (env[i])
	{
		split = ft_split(env[i],'=');
		add_back(&head, addnode(split[0], split[1]));
		i++;
	}
	return (head);
}