/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 23:04:38 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/09 23:07:51 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_op(t_token *token)
{
	if (!token)
		return (0);
	if (is_redir(token) != 0)
		return (1);
	else if (token->type == TOKEN_PIPE)
		return (2);
	return (0);
}

t_exec	*alocate_exec(void)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	exec->args = NULL;
	exec->next = NULL;
	exec->redir = NULL;
	return (exec);
}
//realloc function is used to resize a block of memory that was previously allocated.
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