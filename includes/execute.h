/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:37:01 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/17 04:14:29 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "minishell.h"

typedef struct s_execute	t_execute;
typedef struct s_path		t_path;

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
	int	created_process;
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
#endif