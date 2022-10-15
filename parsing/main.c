/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:39 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/16 00:09:34 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lexer_condition(lexer_t *lexer, t_token *token, char *inpt)
{
	if (lexer)
	{
		token = tokenizer(lexer);
		free(lexer);
		free(inpt);
		check_parse_errors(token);
		g_global.exec = parser(token);
		if (g_global.errorlexer == 1)
		{
			free_tokenizer(token);
			g_global.errorlexer = 0;
			return (1);
		}
		if (g_global.errorparser == 1)
		{
			free_tokenizer(token);
			free_exec(g_global.exec);
			g_global.errorparser = 0;
			return (1);
		}
	}
	return (0);
}

void	remove_env(t_env **env_list)
{
	t_env	*env;

	env = *env_list;
	while (env)
	{
		remove_list(env_list, env);
		env = env->next;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	char	*inpt;
	t_token	*token;
	lexer_t	*lexer;

	(void)argc;
	(void)argv;
	g_global.env_list = get_env_list(env);
	g_global.exitstauts = 0;
	token = NULL;
	signals(0);
	while (1)
	{
		g_global.hd = 1;
		inpt = readline("minishell$ ");
		lexer = init_lexer(inpt);
		add_history(inpt);
		if (lexer_condition(lexer, token, inpt))
			continue ;
		ctrl_d(inpt);
		if (ft_save_pwd())
			g_global.pwd = ft_save_pwd();
		start_execution(g_global.exec, g_global.env_list);
	}
	return (0);
}
