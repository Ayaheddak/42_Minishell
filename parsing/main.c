/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:39 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/18 16:08:48 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list *conv_token_to_list(token_t *token, lexer_t *lexer)
{
	t_list *head;

	head = NULL;
	while ((token = lexer_get_next_token(lexer)) != (void *)0)
	{
		add_back(&head,addnode(token->type, token->value));
	}
	return (head);
	// void print_list(t_list *list)
}
int main()
{
	char *inpt;

	// inpt = readline("Enter text: ");
	// lexer_t *lexer = init_lexer(inpt);
	// token_t *token = (void *)0;

	// while ((token = lexer_get_next_token(lexer)) != (void *)0)
	// {
	// 	printf("token(%d, %s)\n", token->type, token->value);
	// }

	// t_list	*list;

	// list = get_list(ac, av);
	// ft_echo(list);
	while (1)
	{
		inpt = readline("./minishell$ ");
		lexer_t *lexer = init_lexer(inpt);
		token_t *token = (void *)0;
		add_history(inpt);
		 print_list(conv_token_to_list(token, lexer));
		// while ((token = lexer_get_next_token(lexer)) != (void *)0)
		// {
		// 	printf("token(%d, %s)\n", token->type, token->value);
		// }
		// if (strcmp(token->value, "pwd") == 0)
		// 	ft_pwd();
	}
	return (0);
}