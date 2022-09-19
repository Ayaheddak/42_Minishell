/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 05:19:02 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/19 23:26:10 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_exapanded_test()//function for replace expanded
{
	return (strdup("[EXPANDED VALUE]"));
	//return strdup("");
}

lexer_t	*init_lexer(char *str)
{
	lexer_t *lexer = malloc(sizeof(lexer_t));
	lexer->contents = str;
	lexer->i = 0;
	lexer->c = str[lexer->i];
	return(lexer);
}
 
void	lexer_advance(lexer_t *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(lexer_t *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\n' || lexer->c == '\t')
		lexer_advance(lexer);
}

token_t	*lexer_advace_with_token(lexer_t *lexer, token_t *token)
{
	lexer_advance(lexer);
	return (token);
}

char	*lexer_get_current_char_as_string(lexer_t *lexer)
{
	char *str = malloc(sizeof(char) * 2);//edited
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')//to edit
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return 1;
	return 0;
}

int	is_operator_speciaux(char c)
{
	if ((c >=35 && c <= 38) || (c >= 42 && c <= 47) || (c >= 58 && c <= 59) || c == 61 ||
		(c >= 61 && c <= 64) || (c >= 91 && c <= 94) || (c >= 123 && c <= 125) || c == 126)
		return (1);
	return (0);
}

int	check_err(char *str)
{
	int i;
	int s_count;
	int d_count;

	i = 0;
	s_count = 0;
	d_count = 0;
	while (str[i])
	{
		if (str[i] == '"')
			d_count++;
		if (str[i] == 39)
			s_count++;
		i++;
	}
	if(d_count % 2 == 0 && s_count % 2 == 0)
		return (1);
	return (0);
}

token_t	*lexer_get_next_token(lexer_t *lexer)
{
	if (check_err(lexer->contents))
	{
		while (lexer->c != '\0' || lexer->c)
		{
			if (is_whitespace(lexer->c))
				lexer_skip_whitespace (lexer);
			if (lexer->c == '"')
				return lexer_double_quote(lexer);
			else if (lexer->c == 39)
				return lexer_single_quote(lexer);
			else if (lexer->c == '<')
				return (redirection(lexer, TOKEN_IN, TOKEN_DELIMITER, '<'));
			else if (lexer->c == '>')
				return (redirection(lexer, TOKEN_OUT,TOKEN_APPEND, '>'));
			else if (lexer->c == '|')
			{
				return (lexer_advace_with_token(lexer, init_token(TOKEN_PIPE, lexer_get_current_char_as_string(lexer))));
				break;
			}
			else
				return lexer_string(lexer);
		}
	}
	else
		printf("Unclosed quotes\n");
	return (void*)0;
}


// t_list *conv_token_to_list(token_t *token, lexer_t *lexer)
// {
// 	t_list *head;

// 	head = NULL;
// 	while ((token = lexer_get_next_token(lexer)) != (void *)0)
// 	{
// 		add_back(&head,addnode(token->type, token->value));
// 	}
// 	// void print_list(t_list *list)
// }