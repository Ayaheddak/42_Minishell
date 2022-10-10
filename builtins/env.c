/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:48:22 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/10 01:58:33 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_key_value(char *key, char *value)
{
	char	*join;

	join = ft_strjoin(key, "=");
	join = ft_strjoin(join, value);
	return (join);
}

void	print_env(t_env *env, t_execute *exec)
{
	char	*join;

	while (env)
	{
		join = join_key_value(env->key, env->value);
		ft_putstr_fd(join, exec->output);
		ft_putstr_fd("\n", exec->output);
		env = env->next;
	}
}

int	ft_env(t_env *env, char **args, t_execute *exec)
{
	int		i;

	i = 1;
	if (args[i])
		ft_putstr_fd("Invalid input\n", 2);
	else
		print_env(env, exec);
	return (1);
}