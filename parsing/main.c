/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:39 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/18 17:03:47 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list *conv_token_to_list(token_t *token, lexer_t *lexer)
{
	t_list *head;

	head = NULL;
	while ((token = lexer_get_next_token(lexer)) != (void *)0)
	{
		add_back(&head,addnode(&token->type, token->value));
	}
	return (head);
	// void print_list(t_list *list)
}

void	ft_exit()
{
	exit(0);
}

int main()
{
	char *inpt;
	t_list	*list;

	while (1)
	{
		inpt = readline("./minishell$ ");
		lexer_t *lexer = init_lexer(inpt);
		token_t *token = (void *)0;
		add_history(inpt);
		list = conv_token_to_list(token, lexer);
		print_list(list);
	}
	return (0);
}