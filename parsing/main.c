/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:39 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/09 15:41:27 by het-tale         ###   ########.fr       */
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
		env_list = get_env_list(env);
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
		start_execution(g_global.exec, env_list);
	}
	return (0);
}
