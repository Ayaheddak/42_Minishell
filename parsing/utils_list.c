/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 08:13:38 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/09 01:50:00 by het-tale         ###   ########.fr       */
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

void	addback(t_token **head, void *value, void *type)
{
	t_token	*new;
	t_token	*temp;

	new = malloc(sizeof(t_token));
	new->value = value;
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

t_exec	*get_list(void)
{
	t_exec	*t1;
	t_exec	*t2;
	//t_list	*t3;
	char	**args;
	t_redir	*file;
	t_redir	*file1;
	int len;
	
	file = NULL;//malloc(sizeof(t_redir));
	len = 2;
	args = malloc(sizeof(char *) * len);
	args[0] = "cat";
	args[1] = "out";
	// file->type = TOKEN_OUT;
	// file->name = "out";
	t1 = alocate_exec();
	t1->args = args;
	//t1->redir = file;
	file1 = malloc(sizeof(t_redir));
	args = malloc(sizeof(char *) * len);
	args[0] = "wc";
	args[1] = "-l";
	file1->type = TOKEN_OUT;
	file1->name = "out";
	//t2 = new_node(NULL, NULL, args, file1);
	t2 = alocate_exec();
	t2->args = args;
	t2->redir = file1;
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

