/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-tale <het-tale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:35:39 by aheddak           #+#    #+#             */
/*   Updated: 2022/10/18 09:11:14 by het-tale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lexer_condition(t_lexer *lexer, t_token *token, char *inpt)
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

void	leaks_removal(t_leaks **leaks, void *ptr)
{
	t_leaks	*garbage;

	garbage = malloc(sizeof(t_leaks));
	garbage->leak = ptr;
	garbage->next = *(leaks);
	*leaks = garbage;
}

void	free_leaks(t_leaks **env_list)
{
	t_leaks	*env;

	env = *env_list;
	while (env)
	{
		free(*env_list);
		env = env->next;
		*env_list = env;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	char	*inpt;
	t_token	*token;
	t_lexer	*lexer;

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
		start_execution(g_global.exec, g_global.env_list);
	}
	free_leaks(&g_global.g);
	return (0);
}
