/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:09:37 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/29 14:50:48 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "token.h"
# include "lexer.h"
# include "libft.h"
# include "parser.h"
# include "execute.h"
# define EXIT_CODE 0
# define BUFFER_SIZE 42

/*
---------------------- Builtins  ----------------------
*/
void    ft_echo(t_list *list);
void	ft_pwd(t_list *env_list, t_list *head);
void	ft_env(t_list *env_list, t_list *list);
void	ft_change_dir(t_list *list, t_list *env_list);
void    ft_exit(void);
t_list  *ft_unset(t_list *list, t_list *env_list);
void    ft_export(t_list *env_list, t_list *list);
void	ft_call_builtins(t_list *head, t_list *env_list);
/*
----------------------------list management---------------------------------------
*/
t_list  *remove_list(t_list **env_list, t_list *remove);
t_list  *get_list(void);
/*---------------get_next_line------------------------*/
char    *get_next_line(int fd);
char    *extract_line(char *str);
char    *extract_after_line(char *str);
char    *ft_read(int *rb, char *temp, char *buf, int fd);
char    *ft_cpy(char *str, int *i, int *j);
void    skip_line(char *str, int *j);

#endif