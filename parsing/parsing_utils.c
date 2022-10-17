/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 23:04:38 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/17 03:50:34 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_op(t_token *token)
{
	if (!token)
		return (0);
	if (is_redir(token) != 0)
		return (1);
	else if (token->e_type == TOKEN_PIPE)
		return (2);
	return (0);
}

t_exec	*alocate_exec(void)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	leaks_removal(&g_global.g, exec);
	exec->args = NULL;
	exec->next = NULL;
	exec->redir = NULL;
	return (exec);
}

int	len_of_array(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
			i++;
	}
	return (i);
}

char	**ft_realloc(char **args, char *str)
{
	int		i;
	int		len;
	char	**res;

	i = 0;
	len = len_of_array(args);
	res = (char **)malloc(sizeof(char *) * (len + 2));
	leaks_removal(&g_global.g, res);
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = args[i];
		i++;
	}
	free(args);
	res[i] = ft_strdup(str);
	i++;
	res[i] = NULL;
	return (res);
}

void	free_exec(t_exec *exec)
{
	t_exec	*tmp;

	while (exec != NULL)
	{
		tmp = exec;
		exec = exec->next;
		free (tmp);
	}
	free (exec);
}
