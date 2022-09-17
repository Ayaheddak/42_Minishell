// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   unset.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/09/16 21:11:33 by het-tale          #+#    #+#             */
// /*   Updated: 2022/09/17 13:04:22 by het-tale         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

// char	*get_part_one(char *env)
// {
// 	int		i;
// 	char	*pt_one;

// 	i = 0;
// 	while (env[i] && env[i] != '=')
// 		i++;
// 	pt_one = malloc(sizeof(char) * (i + 2));
// 	i = 0;
// 	while (env[i])
// 	{
// 		pt_one[i] = env[i];
// 		if (env[i] == '=')
// 			break ;
// 		i++;
// 	}
// 	pt_one[i] = '\0';
// 	return (pt_one);
// }

// void	ft_unset(t_list *list, char *envp[])
// {
// 	char	*var;
// 	t_args	*temp;
// 	int		i;
// 	char	*unset;
// 	int		j;

// 	temp = list->head->next;
// 	while (temp)
// 	{
// 		i = 0;
// 		while (envp[i])
// 		{
// 			var = get_part_one(envp[i]);
// 			if (!ft_strncmp(var, temp->data, ft_strlen(temp->data)))
// 				envp[i] = "";
// 			i++;
// 		}
// 		temp = temp->next;
// 	}
	
// }