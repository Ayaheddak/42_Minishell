/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:39 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/12 08:10:41 by aheddak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_traverse(t_env *env)
{
	while(env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	char	*inpt;
	t_token	*token;
	t_env	*env_list;
	lexer_t	*lexer;

	(void)argc;
	(void)argv;
	g_global.env = env;
	env_list = get_env_list(g_global.env);
	g_global.env_list = env_list;
	g_global.exitstauts = 0;
	while (1)
	{
		inpt = readline("minishell$ ");//
		if (!inpt)
			continue ;
		lexer = init_lexer(inpt);//
		add_history(inpt);
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
		//system("leaks minishell");
		if (g_global.errorparser == 1)
		{
			free_tokenizer(token);
			free_exec(g_global.exec);
			g_global.errorparser = 0;
			continue ;
		}
		start_execution(g_global.exec, g_global.env_list);
		// printf("The status is: %d\n", g_global.exitstauts);
		//signal(SIGINT, ctrl_c);
		// if (g_global.errorparser == 1)
		// {
		// 	free_tokenizer(token);
		// 	g_global.errorparser = 0;
		// 	continue ;
		// }
		//start_execution(g_global.exec, g_global.env_list);

	}
	return (0);
}
