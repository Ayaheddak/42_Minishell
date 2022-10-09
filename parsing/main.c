/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:39 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/09 22:48:29 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*inpt;
	t_token	*token;
	t_env	*env_list;
	lexer_t	*lexer;

	(void)argc;
	(void)argv;
	env_list = get_env_list(env);
	while (1)
	{
		inpt = readline("./minishell$ ");
		if (!inpt)
			continue ;
		lexer = init_lexer(inpt);
		add_history(inpt);
		token = tokenizer(lexer);
		check_parse_errors(token);
		g_global.exec = parser(token);
		g_global.env_list = env_list;
		if (g_global.errorlexer == 1)
		{
			free_tokenizer(token);
			g_global.errorlexer = 0;
			continue ;
		}
		if (g_global.errorparser == 1)
		{
			free_tokenizer(token);
			free_exec(g_global.exec);
			g_global.errorparser = 0;
			continue ;
		}
		start_execution(g_global.exec, g_global.env_list);
	}
	return (0);
}
