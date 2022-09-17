/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:01:59 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/17 14:48:11 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int valid_option(char *str)
{
    size_t	len;
    size_t	i;
    int d;

    len = ft_strlen(str);
    i = 1;
    d = -1;
    if (str[0] == '-')
    {
        d = 0;
        while (i < len)
        {
            if (str[i] != 'n')
                d = 1;
            i++;
        }
    }
    if (d < 0 || d == 1)
        return (0);
    return (1);
}

void	ft_echo(t_list *list)
{
	t_list  *temp;

	if (!list)
		return ;
	temp = list->next;
	if (temp && valid_option(temp->data))
    {
		temp = temp->next;
        while (temp)
        {
			printf("%s", (char *)temp->data);
            if (temp->next)
				printf(" ");
            temp = temp->next;
        }
    }
	else
	{
		while (temp)
        {
            printf("%s", (char *)temp->data);
            if (temp->next)
				printf(" ");
            temp = temp->next;
        }
		printf("\n");
    }
}