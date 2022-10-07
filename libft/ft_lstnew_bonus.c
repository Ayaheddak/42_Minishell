/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:13:54 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/30 20:04:08 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list *ft_lstnew(void *content)
{
	t_list *new;

	new = (t_list*) malloc (sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next  = NULL;
	return (new);
}
