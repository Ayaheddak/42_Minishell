/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 20:30:20 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/09 01:38:08 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redir(t_token *token)
{
	if (token->type == TOKEN_APPEND || token->type == TOKEN_DELIMITER
		|| token->type == TOKEN_IN || token->type == TOKEN_OUT)
		return (token->type);
	return (0);
}

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

void	*check_parse_errors(t_token *head)
{
	t_token	*token;
	int		i;

	i = 0;
	token = head;
	while (token != NULL)
	{
		if ((i == 0 && is_op(token) == 2)
			|| (token->next == NULL && is_op(token) > 0))
			return (ft_errer(2));
		else if (is_op(token) == 1 && is_op(token->next) > 0)
			return (ft_errer(2));
		else if (is_op(token) == 2 && is_op(token->next) == 2)
			return (ft_errer(2));
		i++;
		token = token->next;
	}
	return ((void *)0);
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

t_exec	*parser(t_token *head)
{
	t_token	*token;
	t_exec	*exec;

	token = head;
	exec = alocate_exec();
	while (token)
	{
		if (token == NULL)
		{
			exec->next = NULL;
			break ;
		}
		if (token->type == TOKEN_PIPE)
		{
			exec->next = parser(token->next);
			break ;
		}
		if (token->type == TOKEN_STRING)
			exec->args = ft_realloc(exec->args, token->value);
		if (is_redir(token) != 0 && token->next)
		{
			addredirection(&exec->redir, is_redir(token), token->next->value);
			token = token->next;
		}
		if (token)
			token = token->next;
	}
	return (exec);
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
