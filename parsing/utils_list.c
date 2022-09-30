/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 08:13:38 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/30 13:28:50 by het-tale         ###   ########.fr       */
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

void	add_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp == NULL)
		*lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	print_list(t_list *list)
{
	int	i;

	i = 0;
	while (list != NULL)
	{
		printf("------------- Node numbre %d  = -------------\n", i);
		printf("ur id = %s\n", (char *)list->id);
		printf("ur value = %s\n", (char *)list->data);
		i++;
		list = list->next;
	}
}

// void add_front(t_list **lst, t_list *new)
// {
// 	new->next=*lst;
// 	*lst = new;
// }

int	get_size(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_list	*get_list(void)
{
	t_list	*t1;
	t_list	*t2;
	//t_list	*t3;
	char	**args;
	t_file	*file;
	t_file	*file1;
	int len;
	
	file = malloc(sizeof(t_file));
	len = 2;
	args = malloc(sizeof(char *) * len);
	args[0] = "cat";
	args[1] = "-e";
	file->type = TOKEN_DELIMITER;
	file->name = "end";
	t1 = new_node(NULL, NULL, args, file);
	file1 = malloc(sizeof(t_file));
	args = malloc(sizeof(char *) * len);
	args[0] = "wc";
	args[1] = "-l";
	file1->type = TOKEN_OUT;
	file1->name = "f3";
	t2 = new_node(NULL, NULL, args, file1);
	// len = 1;
	// file->type = TOKEN_OUT;
	// file->name = "f3";
	// args = malloc(sizeof(char *) * len);
	// args[0] = "wc";
	// t3 = new_node(NULL, NULL, args, file);
	t1->next = t2;
	//t2->next = t3;
	return (t1);
}
