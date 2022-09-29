# 42_Minishell

**Create our own shell**

## The Execution Part:

*In this part we are required to handle pipes and implement redirections*

This is The main list of the project:

`typedef struct s_list { void	*data; void	*id; char	**args; t_file	*file; struct s_list *next;}t_list;`

- `data` : The data read from STDIN with readline.
- `id` : The id of the data. it differs based on the type of data for example if it's a *pipe* the *id* will equal 1.
- `args` : store the commands and their options.
- `file` : a struct wich contains a type and name of the file. it allows us to know how to open our files.

For testing purpose we created a list as follows:

| args: echo hello    | args: cat file | args: wc
| file : NULL         | file: NULL     | file: type = 3, name = f1


should behave like : `echo hello | cat file | wc > f1`


