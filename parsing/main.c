/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:39 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/14 23:50:24 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*inpt;
	t_token	*token;
	lexer_t	*lexer;

	(void)argc;
	(void)argv;
	g_global.env_list = get_env_list(env);
	g_global.exitstauts = 0;
	signals(0);
	while (1)
	{
		g_global.hd = 1;
		inpt = readline("minishell$ ");
		lexer = init_lexer(inpt);
		add_history(inpt);
		if (lexer)
		{
			token = tokenizer(lexer);//
			free(lexer);
			free(inpt);
			
			check_parse_errors(token);
			g_global.exec = parser(token);
			if (g_global.errorlexer == 1)
			{
				free_tokenizer(token);
				g_global.errorlexer = 0;
				continue ;
			}
			
		}
		ctrl_d(inpt);
		start_execution(g_global.exec, g_global.env_list);
	}
	return (0);
}
