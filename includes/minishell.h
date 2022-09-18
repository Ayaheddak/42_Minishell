/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:09:37 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/18 16:47:39 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "token.h"
# include "lexer.h"
# include "libft.h"

/*
---------------------- Builtins  ----------------------
*/
void    ft_echo(t_list *list);
void	ft_pwd(void);
// void	ft_env(char *envp[], t_args *option);
void	ft_change_dir(t_list *list);
// void	ft_unset(t_list *list, char *envp[]);
// int		ft_lst_size(t_list *list);

#endif