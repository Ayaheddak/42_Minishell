/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 02:15:52 by het-tale          #+#    #+#             */
/*   Updated: 2022/10/17 07:36:14 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	remove_specials(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_operator_speciaux(str[i]) || is_whitespace(str[i]))
			return (i);
	}
	return (-1);
}

void	expansion_utils(int temp_fd, char *line, char *tmp)
{
	char	*substr;
	int		rmv;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			rmv = remove_specials(line + i + 1);
			if (rmv != -1)
				substr = ft_substr(line + i, 1, rmv);
			else
				substr = ft_substr(line + i, 1, ft_strlen(line));
			tmp = get_expanded(substr);
			if (tmp)
				write(temp_fd, tmp, ft_strlen(tmp));
			i += ft_strlen(substr);
		}
		else
			write(temp_fd, &line[i], 1);
		i++;
	}
}

void	expansion_inside_hrdc(int temp_fd, char *line, char *tmp)
{
	char	*str;

	str = ft_strchr(line, '$');
	if (str)
		expansion_utils(temp_fd, line, tmp);
	else
		write(temp_fd, line, ft_strlen(line));
}

void	read_from_hrdc(pid_t pd, t_exec *exec_list, int temp_fd)
{
	char	*line;
	char	*tmp;

	line = "";
	tmp = NULL;
	if (!pd)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline("> ");
			if (line == NULL)
				exit(0);
			if (!ft_strcmp(exec_list->redir->name, line))
			{
				free(line);
				exit(0);
			}
			expansion_inside_hrdc(temp_fd, line, tmp);
			write(temp_fd, "\n", 1);
			free(line);
		}
	}
}

void	here_doc(int *d, t_execute *exec, t_exec *exec_list)
{
	int		temp_fd;
	pid_t	pd;
	int		st;

	temp_fd = open("temp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pd = fork();
	read_from_hrdc(pd, exec_list, temp_fd);
	waitpid(pd, &st, 0);
	if (WIFEXITED(st))
		g_global.exitstauts = WEXITSTATUS(st);
	close(temp_fd);
	exec->input = open("temp_file", O_RDONLY, 0444);
	*d = 0;
}
