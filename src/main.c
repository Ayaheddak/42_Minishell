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
		token = lexer_get_next_token(lexer);
		if (strcmp(token->value, "pwd") == 0)
			ft_pwd();
	}
	return (0);
}