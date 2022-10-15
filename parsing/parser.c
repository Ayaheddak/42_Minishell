/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 20:30:20 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/15 05:50:45 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

// int	cond_parsing(t_token *token, t_exec *exec)
// {
// 	if (token == NULL)
// 	{
// 		exec->next = NULL;
// 		return (1);
// 	}
// 	if (token->type == TOKEN_PIPE)
// 	{
// 		exec->next = parser(token->next);
// 		return (2);
// 	}
// 	return (0);
// 	// if (is_redir(token) != 0 && token->next)
// 	// {
// 	// 	addredirection(&exec->redir, is_redir(token), token->next->value);
// 	// 	token = token->next;
// 	// }
// 	// return (3);
// }

t_exec	*parser(t_token *head)
{
	t_token	*token;
	t_exec	*exec;
	char	**split;
	int		i;

	i = 0;
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
		{
			if (!token->split)
				exec->args = ft_realloc(exec->args, token->value);
			else
			{
				split = ft_split(token->value, ' ');
				while (split[i])
					exec->args = ft_realloc(exec->args, split[i++]);
				free_tab(split);
			}
		}
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

void	free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free (str);
}
