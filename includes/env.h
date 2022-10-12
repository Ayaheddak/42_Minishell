/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:51:32 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/12 02:34:47 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env	t_env;

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

t_env	*create_node(char *key, char *value);
void	add_back_env(t_env **env_head, t_env *new);
void	add_front_env(t_env **env_head, t_env *new);
int		get_list_len(t_env	*list);
char	**get_env_array(t_env *env);
t_env	*get_env_list(char *env[]);
char	*get_env_value(t_env *env, char *key);
t_env	*ft_copy_env(t_env *env);
t_env	*ft_sort_env(t_env *env);
void	free_env(t_env *env);
#endif