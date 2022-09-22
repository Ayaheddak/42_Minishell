/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:09:37 by het-tale          #+#    #+#             */
/*   Updated: 2022/09/22 04:17:05 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "token.h"
# include "parser.h"
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# include "libft.h"
# include "lexer.h"
# include "token.h"
# include "parser.h"

# define    EXIT_CODE 0

/*
---------------------- Builtins ---------------------- 
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
---------------------- list management ---------------------- 
*/
t_list  *remove_list(t_list **env_list, t_list *remove);

#endif