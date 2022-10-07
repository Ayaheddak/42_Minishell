/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 12:16:56 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/30 20:04:42 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *tmp;

	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while(tmp->next)
		tmp  = tmp->next;
	tmp->next = new;
}
