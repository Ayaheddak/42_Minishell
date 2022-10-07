/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:49 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/07 00:07:51 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *init_token(int type, char *value)
{
	t_token *token = malloc (sizeof(t_token));
	token->type = type;
	token->value = value;
	return (token);
}

t_token	*lexer_get_next_token(lexer_t *lexer)
{
	while (lexer->c != '\0')
	{
		if (is_whitespace(lexer->c))
			lexer_skip_whitespace (lexer);
		else if (lexer->c == '"') 
			return (lexer_double_quote(lexer));
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
	return (void*)0;
}

t_token *tokenizer(lexer_t *lexer)
{
	t_token	*head;
	t_token	*token;

	head = NULL;
	while ((token = lexer_get_next_token(lexer)) != (void *)0)
		addback(&head, token->value, &token->type);
	return (head);
}

void print_tokenizer(t_token *token)
{
	int i;
	t_token *tmp;
	
	i = 0;
    while(token != NULL)
    {
		printf("------------- Node numbre %d  = -------------\n" , i);
        printf("ur value = %s\n", (char *)token->value);
		printf("ur type = %d\n",token->type);  
        tmp = token;
		token = token->next;
		if (tmp->value)
			free(tmp->value);
		free (tmp);
		i++;
    }
}

void	free_tokenizer(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free (tmp);
	}
	free (token);
}
