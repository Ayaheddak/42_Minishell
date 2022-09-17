/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:29:48 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/17 15:15:35 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_change_dir(t_list *list)
{
	t_list	*temp;
	int		len;
	int		change;

    if (!list)
		return ;
	temp = list->next;
	len = get_size(list);
	change = 0;
	if (len > 2)
		write(2, "too many arguments\n", 19);
	else if (len == 1)
		change = chdir(getenv("HOME"));
	else if (temp)
	{
		if (!ft_strncmp(temp->data, ".", ft_strlen(temp->data)) || !ft_strncmp(temp->data, "..", ft_strlen(temp->data)))
			printf("Dear programmer we accept either absolute or relative paths ok?\n");
		else
			change = chdir(temp->data);
	}
	if (change == -1)
		perror("Error");
}