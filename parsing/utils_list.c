/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 08:13:38 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/18 16:15:33 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*addnode(int id, void *data)
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
		printf("ur id = %d\n",list->id);
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
// 	t_list	*list;

// 	list = get_list(ac, av);
// 	(void)list;
// 	printf("%s\n", (char *)list->data);
// 	printf("%d\n", get_size(list));
// 	printf("%s\n", (char *)list->data);
// }