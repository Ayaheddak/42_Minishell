/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:56:10 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/12 09:21:48 by aheddak          ###   ########.fr       */
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
		split = ft_split(env[i],'=');
		add_back_env(&head, create_node(split[0], split[1]));
		i++;
	}
	// for (int i = 0; split[i]; i++)
	// 	free(split[i]);
	// free(split);
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
	while(env)
	{
		add_back_env(&env_copy, create_node(env->key, env->value));
		env = env->next;
	}
	return (env_copy);
}

t_env	*ft_sort_env(t_env *env_list)
{
	char	*temp_key;
	char	*temp_value;
	t_env	*env;
	int		i;
	int		j;
	int		len;

	i = 0;
	len = get_list_len(env_list);
	while (i < len)
	{
		env = env_list;
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp(env->key, env->next->key) > 0)
			{
				temp_key = ft_strdup(env->key);
				temp_value = ft_strdup(env->value);
				env->key = ft_strdup(env->next->key);
				env->value = ft_strdup(env->next->value);
				env->next->key = ft_strdup(temp_key);
				env->next->value = ft_strdup(temp_value);
			}
			env = env->next;
			j++;
		}
		i++;
	}
	return (env);
}