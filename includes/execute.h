/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:37:01 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/08 12:12:04 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "minishell.h"

typedef struct s_execute	t_execute;
typedef struct s_path	t_path;

struct s_execute
{
	int	infile;
	int	out_file;
	int	*fd_pipe;
	int	status;
	int	*child_pid;
	int	input;
	int	output;
	int	nb_cmd;
	int	cmd_index;
};

struct s_path
{
	int		i;
	int		j;
	char	**split;
	size_t	len;
	char	*path;
	int		d;
};

/*---------------------Redirections--------------*/
void	redirection_handling(t_list	*list);
void	ft_error(char *str);
// /*--------------------Check commands------------*/
// char	*check_command(char *cmd, t_env *env);
// char	*get_right_path(t_env *env, char *cmd);
// char	*get_right_path_utils(t_path *corr_path, char *cmd, t_env *env);
// void	execute_command(t_execute *exec, char **cmd, t_env *env);
// /*--------------------create children---------------*/
// void	start_execution(t_exec *exec_list, t_env *env);
// void	input_output(int i, t_execute *exec, t_exec *exec_list);
// void	ft_error(char *str);
// void	close_pipes(t_execute *exec, int n);
// void	close_and_free(t_execute exec, int n);
// void    file_exist(int  *d, t_execute *exec, t_exec *exec_list);
#endif