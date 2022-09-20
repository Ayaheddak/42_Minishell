/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:03:47 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/20 10:54:31 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_') || (str[i] == '=')))
		{
			printf("dkhli dkhli chy hja m9ada hdchy madayzch !(I miss u btw ;))\n");//yalah hayd elia mn hna ,i miss u moree !!
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_replaced(t_list *env_list, char *search, char *replace)
{
	t_list	*env_iter;

	env_iter = env_list;
	while (env_iter)
	{
		if (!ft_strncmp(search, env_iter->id, ft_strlen(search)))
		{
			env_iter->data = replace;
			return (1);
		}
		env_iter = env_iter->next;
	}
	return (0);
}

void	ft_export(t_list *env_list, t_list *list)
{
	t_list	*temp;
	char	**split;

	temp = list->next;
	if (temp && !is_valid_arg(temp->data))
		return ;
	while (temp)
	{
		if (ft_strchr(temp->data, '='))
		{
			split = ft_split(temp->data, '=');
			if(!split[1])
				split[1] = "";
			if (is_replaced(env_list, split[0], split[1]))
				break ;
			add_back(&env_list, addnode(split[0], split[1]));
		}
		temp = temp->next;
	}
}