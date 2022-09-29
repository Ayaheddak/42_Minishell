/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:39 by aheddak           #+#    #+#             */
/*   Updated: 2022/09/29 20:56:43 by het-tale         ###   ########.fr       */
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
}

int main(int argc, char *argv[], char *env[])
{
	char	*inpt;
	t_list	*list;
	t_env	*env_list;
	t_list	*exec_list;

	(void)argc;
	(void)argv;
	(void)env;
	// env_list = get_env_list(env);
	env_list = malloc(sizeof(t_env));
	env_list->key = "PATH";
	env_list->value = "/home/het-tale/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin";
	while (1)
	{
		inpt = readline("./minishell$ ");
		lexer_t *lexer = init_lexer(inpt);
		token_t *token = (void *)0;
		add_history(inpt);
		list = conv_token_to_list(token, lexer);
		(void)list;
		exec_list = get_list();
		(void)exec_list;
		start_execution(exec_list, env_list);
	}
	return (0);
}