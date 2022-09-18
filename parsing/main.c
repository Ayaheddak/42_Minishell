/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:39 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/18 05:43:01 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
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
		while ((token = lexer_get_next_token(lexer)) != (void *)0)
		{
			printf("token(%d, %s)\n", token->type, token->value);
		}
		// if (strcmp(token->value, "pwd") == 0)
		// 	ft_pwd();
	}
	return (0);
}