/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:47:09 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/09 22:49:46 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(char **args, t_env *env, t_execute *exec)
{
	char	*value;

	if (args[1])
		ft_putstr_fd("Invalid input\n", 2);
	else
	{
		value = get_env_value(env, "PWD");
		if (value)
		{
			ft_putstr_fd(value, exec->output);
			ft_putstr_fd("\n", exec->output);
		}
	}
	return (1);
}
