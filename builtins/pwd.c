/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:47:09 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/19 21:44:45 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_list *env_list, t_list *head)
{
	t_list	*temp;
	char	*str;
	t_list	*tmp;

	temp = env_list;
	tmp = head->next;
	if (tmp)
	{
		str = tmp->data;
		if (str[0] == '-')
		{
			write(2, "invalid option\n", 15);
			return ;
		}
	}
	while (temp)
	{
		if (!ft_strncmp(temp->id, "PWD", ft_strlen(temp->id)))
		{
			printf("%s\n", (char *)temp->data);
			break ;
		}
		temp = temp->next;
	}
}

