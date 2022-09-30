/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:58:24 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/30 12:58:43 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_HANDLING_H
# define ENV_HANDLING_H

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
#endif