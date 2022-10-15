/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:56:10 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/15 01:48:18 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//to free
t_env	*get_env_list(char *env[])
{
	int		i;
	char	**split;
	t_env	*head;

	i = 0;
	head = NULL;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		add_back_env(&head, create_node(split[0], split[1]));
		i++;
	}
	return (head);
}

char	**get_env_array(t_env *env)
{
	char	**str_env;
	int		len;
	int		i;

	len = get_list_len(env);
	str_env = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (env)
	{
		str_env[i] = ft_strjoin(env->key, "=");
		str_env[i] = ft_strjoin(str_env[i], env->value);
		env = env->next;
		i++;
	}
	str_env[i] = NULL;
	return (str_env);
}

t_env	*ft_copy_env(t_env *env)
{
	t_env	*env_copy;

	env_copy = NULL;
	while (env)
	{
		add_back_env(&env_copy, create_node(env->key, env->value));
		env = env->next;
	}
	return (env_copy);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env;
		free(env->key);
		free(env->value);
		env = env->next;
		free (tmp);
	}
	free (env);
}
