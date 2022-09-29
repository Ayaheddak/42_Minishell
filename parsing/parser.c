// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parser.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/09/20 11:30:59 by aheddak           #+#    #+#             */
// /*   Updated: 2022/09/29 22:09:06 by het-tale         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

// void add_back_cmd(t_cmd **lst, t_cmd *new)
// {
// 	t_cmd *tmp;

// 	tmp = *lst;
// 	if (tmp == NULL)
// 		*lst = new;
// 	else
// 	{
// 		while(tmp->next != NULL)
// 			tmp = tmp->next;
// 		tmp->next = new;
// 	}
// }

// void add_back_redir(t_redir **lst, t_redir *new)
// {
// 	t_redir *tmp;

// 	tmp = *lst;
// 	if (tmp == NULL)
// 		*lst = new;
// 	else
// 	{
// 		while(tmp->next != NULL)
// 			tmp = tmp->next;
// 		tmp->next = new;
// 	}
// }
// void add_back_exec(t_exec **lst, t_exec *new)
// {
// 	t_exec *tmp;

// 	tmp = *lst;
// 	if (tmp == NULL)
// 		*lst = new;
// 	else
// 	{
// 		while(tmp->next != NULL)
// 			tmp = tmp->next;
// 		tmp->next = new;
// 	}
// }
// void print_list_parser(t_exec *list)
// {
// 	int i;

// 	i = 0;
// 	while (list != NULL)
// 	{
// 		printf("------------- Node numbre %d  = -------------\n" , i);
// 		// printf("ur id = %d\n",*(int*)list->cmd);
// 		// printf("ur value = %s\n", (char*)list->redir);
// 		printf("ur cmd = %s\n",(void *)list->cmd);
// 		printf("ur redir = %s\n", (void*)list->redir);
// 		i++;
// 		list = list->next;
// 	}
// }
// void print_cmd(t_cmd *list)
// {
// 	int i;

// 	i = 0;
// 	while (list != NULL)
// 	{
// 	printf("bef\n");
// 		printf("------------- Node numbre %d  = -------------\n" , i);
// 		printf("ur value = %s\n",list->cmd);
// 		//printf("ur value = %s\n", (char*)list->data);
// 		i++;
// 		list = list->next;
// 	}
// }
// int search(t_list *list, int id)
// {
// 	t_list *tmp;
	
// 	tmp = list;
//     while (tmp != NULL) 
// 	{
//         if (*(int *)tmp->id == id)
//             return (1);
//         tmp = tmp->next;
//     }
//     return (0);
// }

// void parser(t_list *list)
// {
// 	t_list *tmp;
// 	t_exec *exec;

// 	exec = malloc(sizeof(t_exec));
// 	exec->cmd =  NULL;
// 	exec->redir = NULL;
// 	tmp = list;
// 	//while (tmp != NULL)
// 	//{
// 		while(tmp != NULL)// && *(int *)tmp->id != TOKEN_PIPE)
// 		{
// 		printf("node --> %s\n", tmp->data);
// 		if (*(int *)tmp->id == TOKEN_PIPE)
// 		{
// 			printf("exit pipe\n");
// 			break;
// 		}
// 		if (*(int *)tmp->id == TOKEN_IN)
// 		{
// 			tmp = tmp->next;
// 			t_redir *newnode = (t_redir *)malloc(sizeof(t_redir));
// 			newnode->type = TOKEN_IN;
// 			newnode->file = tmp->data;
// 			newnode->next = NULL;
// 			add_back_redir(&exec->redir, newnode);
// 		}
// 		else if (*(int *)tmp->id == TOKEN_OUT)
// 		{
// 			tmp = tmp->next;
// 			t_redir *newnode = (t_redir *)malloc(sizeof(t_redir));
// 			newnode->type = TOKEN_OUT;
// 			newnode->file = tmp->data;
// 			newnode->next = NULL;
// 			add_back_redir(&exec->redir, newnode);
// 		}
// 		else if (*(int *)tmp->id == TOKEN_APPEND)
// 		{
// 			tmp = tmp->next;
// 			t_redir *newnode = (t_redir *)malloc(sizeof(t_redir));
// 			newnode->type = TOKEN_APPEND;
// 			newnode->file = tmp->data;
// 			newnode->next = NULL;
// 			add_back_redir(&exec->redir, newnode);
// 		}
// 		else if (*(int *)tmp->id == TOKEN_DELIMITER)
// 		{
// 			tmp = tmp->next;
// 			t_redir *newnode = (t_redir *)malloc(sizeof(t_redir));
// 			newnode->type = TOKEN_DELIMITER;
// 			newnode->file = tmp->data;
// 			newnode->next = NULL;
// 			add_back_redir(&exec->redir, newnode);
// 		}
// 		else if (*(int *)tmp->id == TOKEN_STRING)
// 		{
// 			t_cmd *newnode = (t_cmd *)malloc(sizeof(t_cmd));
// 			newnode->cmd = tmp->data;
// 			newnode->next = NULL;
// 			add_back_cmd(&exec->cmd, newnode);
// 		}
// 		tmp = tmp->next;
// 	}
// 	// if (tmp == NULL)
// 	// 	break;
// 	// tmp = tmp->next;
// 	// exec =  exec->next;
// 	//}
// }
