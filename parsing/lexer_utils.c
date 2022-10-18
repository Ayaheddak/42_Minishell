/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:59:16 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/18 00:16:50 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	is_operator_speciaux(char c)
{
	if ((c >= 35 && c < 39) || (c >= 42 && c <= 47) || (c >= 58 && c <= 59)
		|| (c >= 60 && c <= 64) || (c >= 91 && c <= 94)
		|| (c >= 123 && c <= 125) || c == 126)
		return (1);
	return (0);
}

void	*ft_errer(int i)
{
	if (i == 1)
	{
		g_global.errorlexer = 1;
		ft_putstr_fd("Error : Unclosed quotes\n", 2);
	}
	if (i == 2)
	{
		g_global.errorparser = 1;
		ft_putstr_fd("Error : Synthax Error \n", 2);
	}
	return ((void *)0);
}

int	is_redir(t_token *token)
{
	if (token->e_type == TOKEN_APPEND || token->e_type == TOKEN_DELIMITER
		|| token->e_type == TOKEN_IN || token->e_type == TOKEN_OUT)
		return (token->e_type);
	return (0);
}
