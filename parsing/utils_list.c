/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 08:13:38 by aheddak           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/29 16:49:11 by het-tale         ###   ########.fr       */
=======
/*   Updated: 2022/09/22 17:02:09 by aheddak          ###   ########.fr       */
>>>>>>> 4467661d4eb95413f90b1f5804a44b29e785b5e1
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*addnode(void *id, void *data)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->id = id;
	newnode->data = data;
	newnode->next = NULL;
	return (newnode);
}

t_list	*new_node(void *id, void *data, char **args, t_file *file)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->data = data;
	newnode->id = id;
	newnode->args = args;
	newnode->file = file;
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
		printf("ur id = %s\n",(char *)list->id);
		printf("ur value = %s\n", (char*)list->data);
		i++;
		list = list->next;
	}
}

// void add_front(t_list **lst, t_list *new)
// {
// 	new->next=*lst;
// 	*lst = new;
// }

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

t_list  *get_list(void)
{
	t_list	*t1;
	t_list	*t2;
	t_list	*t3;
	char	**args;
	t_file	*file;
	int len;
	
	len = 2;
	args = malloc(sizeof(char *) * len);
	args[0] = "echo";
	args[1] = "hello";
	t1 = new_node(NULL, NULL, args, NULL);
	args = malloc(sizeof(char *) * len);
	args[0] = "cat";
	args[1] = "file";
	t2 = new_node(NULL, NULL, args, NULL);
	len = 1;
	file = malloc(sizeof(t_file));
	file->type = TOKEN_OUT;
	file->name = "f1";
	args = malloc(sizeof(char *) * len);
	args[0] = "wc";
	t3 = new_node(NULL, NULL, args, file);
	t1->next = t2;
	t2->next = t3;
	return (t1);
}

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