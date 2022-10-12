/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheddak <aheddak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:39 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/12 03:16:45 by aheddak          ###   ########.fr       */
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
<<<<<<< HEAD
		//check_parse_errors(token);
		//g_global.exec = parser(token);
=======
		check_parse_errors(token);
		g_global.exec = parser(token);
<<<<<<< HEAD
=======
>>>>>>> 03deedc11116139d996e838ea2e331703f9faf25
		//g_global.env_list = env_list;
>>>>>>> 98b599f56eacc72152541b7c3067d1a4e89a4525
		if (g_global.errorlexer == 1)
		{
			free_tokenizer(token);
			g_global.errorlexer = 0;
			continue ;
		}
		print_tokenizer(token);
		//system("leaks minishell");
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 03deedc11116139d996e838ea2e331703f9faf25
		// if (g_global.errorparser == 1)
		// {
		// 	free_tokenizer(token);
		// 	free_exec(g_global.exec);
		// 	g_global.errorparser = 0;
		// 	continue ;
		// }
<<<<<<< HEAD
=======
		start_execution(g_global.exec, g_global.env_list);
		// printf("The status is: %d\n", g_global.exitstauts);
		signal(SIGINT, ctrl_c);
=======
		if (g_global.errorparser == 1)
		{
			free_tokenizer(token);
			free_exec(g_global.exec);
			g_global.errorparser = 0;
			continue ;
		}
>>>>>>> 03deedc11116139d996e838ea2e331703f9faf25
		//start_execution(g_global.exec, g_global.env_list);
>>>>>>> 98b599f56eacc72152541b7c3067d1a4e89a4525
	}
	return (0);
}
