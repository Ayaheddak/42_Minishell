/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 20:30:20 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/17 03:50:34 by het-tale         ###   ########.fr       */
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

// int		cond_parsing2(t_token *token, t_exec *exec)
// {
// 	if (token == NULL)
// 	{
// 		exec->next = NULL;
// 		return (1);
// 	}
// 	if (token->e_type == TOKEN_PIPE)
// 	{
// 		exec->next = parser(token->next);
// 		return (1);
// 	}
// 	return (0);
// }

// void	cond_parsing(t_token **token, t_exec **exec, int *ret)
// {
// 	char	**split;
// 	int		i;

// 	i = 0;
// 	if (cond_parsing2(*token, *exec) == 1)
// 		*ret = 1;
// 	if ((*token)->type == TOKEN_STRING && (*token)->next)
// 	{
// 		if (!(*token)->split)
// 			(*exec)->args = ft_realloc((*exec)->args, (*token)->value);
// 		else
// 		{
// 			split = ft_split((*token)->value, ' ');
// 			while (split[i])
// 				(*exec)->args = ft_realloc((*exec)->args, split[i++]);
// 			free_tab(split);
// 		}
// 	}
// 	if (is_redir(*token) != 0 && (*token)->next)
// 	{
// 			addredirection(&(*exec)->redir, is_redir(*token), (*token)->next->value);
// 			*token = (*token)->next;
// 	}
// 	if (*token)
// 		*token = (*token)->next;
// }
// t_exec	*parser(t_token *head)
// {
// 	t_token	*token;
// 	t_exec	*exec;
// 	int		ret;

// 	ret = 0;
// 	token = head;
// 	exec = alocate_exec();
// 	while (token)
// 	{
// 		cond_parsing(&token, &exec, &ret);
// 		if (ret == 1)
// 			break ;
// 	}
// 	///printf("args[0]--> %s\n", exec->args[0]);
// 	return (exec);
// 	// print_redir(exec->redir);
//}
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
		if (token->e_type == TOKEN_PIPE)
		{
			exec->next = parser(token->next);
			break ;
		}
		if (token->e_type == TOKEN_STRING)
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
			if (!token->next->split)
				addredirection(&exec->redir, is_redir(token), token->next->value);
			else
				addredirection(&exec->redir, AMBIGUOUS_REDIR, token->next->value);
			token = token->next;
		}
		if (token)
			token = token->next;
	}
	return (exec);
}

