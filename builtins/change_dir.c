/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:29:48 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/20 10:53:24 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_change_dir(t_list *list, t_list *env_list)
{
	t_list	*temp;
	t_list	*tmp;
	t_list	*pwd;
	int		len;
	int		change;

    if (!list)
		return ;
	temp = list->next;
	tmp = env_list;
	change = 0;
	len = get_size(list);
	if (len > 2)
		write(2, "too many arguments\n", 19);
	else if (len == 1 || temp->data == NULL)
	{
		while (tmp)
		{
			if (!ft_strncmp(tmp->id, "HOME", ft_strlen(tmp->id)))
			{
				pwd = env_list;
				change = chdir(tmp->data);
				while (pwd)
				{
					if (!ft_strncmp(pwd->id, "PWD", ft_strlen(pwd->id)))
					{
						pwd->data = getcwd(tmp->data, 100);
						break ;
					}
					pwd = pwd->next;
				}
			}
			tmp = tmp->next;
		}
	}
	else if (temp)
	{
		if (!ft_strncmp(temp->data, ".", ft_strlen(temp->data)) || !ft_strncmp(temp->data, "..", ft_strlen(temp->data)))
			printf("Dear programmer we accept either absolute or relative paths ok?\n");// wlah mateaseeb azayn '_'
		else
		{
			change = chdir(temp->data);
			tmp = env_list;
			while (tmp)
			{
				if (!ft_strncmp(tmp->id, "PWD", ft_strlen(tmp->id)))
				{
					tmp->data = getcwd(tmp->data, 100);
					break ;
				}
				tmp = tmp->next;
			}
		}
	}
	if (change == -1)
		perror("Error");
}