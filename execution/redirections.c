// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   redirections.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/09/22 16:35:47 by het-tale          #+#    #+#             */
// /*   Updated: 2022/09/29 14:49:49 by het-tale         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

// void	redirection_handling(t_list	*list)
// {
// 	t_list	*temp;
// 	int		out_file;
// 	int		in_file;
// 	char	*line;
// 	int		temp_fd;

// 	temp = list;
// 	while (temp)
// 	{
// 		if (!ft_strcmp(temp->data, ">") && temp->next->data)
// 		{
// 			out_file = open(temp->next->data, O_CREAT | O_TRUNC | O_RDWR, 0777);
// 			if (out_file < 0)
// 				ft_error("outfile error");
// 			if (dup2(out_file, 1) == -1)
// 				ft_error("Redirecting output error");
// 		}
// 		else if (!ft_strcmp(temp->data, ">>") && temp->next->data)
// 		{
// 			out_file = open(temp->next->data, O_CREAT | O_APPEND | O_RDWR, 0777);
// 			if (out_file < 0)
// 				ft_error("outfile error");
// 			if (dup2(out_file, 1) == -1)
// 				ft_error("Redirecting output error");
// 		}
// 		else if (!ft_strcmp(temp->data, "<") && temp->next->data)
// 		{
// 			in_file = open(temp->next->data, O_RDONLY, 0444);
// 			if (in_file < 0)
// 				ft_error("infile error");
// 			if (dup2(in_file, 0) == -1)
// 				ft_error("Redirecting input error");
// 		}
// 		else if (!ft_strcmp(temp->data, "<<") && temp->next->data)
// 		{
// 			temp_fd = open("temp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 			line = "";
// 			while (1)
// 			{
// 				line = get_next_line(0);
// 				if (line == NULL)
// 					break ;
// 				if (!ft_strcmp(temp->next->data, line))
// 				{
// 					free(line);
// 					break ;
// 				}
// 				write(temp_fd, line, ft_strlen(line));
// 				free(line);
// 			}
// 			close(temp_fd);
// 			temp_fd = open("temp_file", O_RDONLY, 0444);
// 			if (dup2(temp_fd, 0) == -1)
// 				ft_error("Redirecting input error");
// 		}
// 		temp = temp->next;
// 	}
// 	exit(0);
// }