#include "../includes/minishell.h"


//init singleton for "global" use *replaces global variables
t_data *get_data(void)
{
	static t_data *data;

	data = NULL;

	if(data == NULL)
		data = (t_data *)malloc(sizeof(t_data));
	return (data);
}

//exit and free all data
void exit_all(void)
{
	t_data *data;

	data = get_data();
	free(data);
}

void init_data(void)
{
	t_data *data;

	data = get_data();
	data->line = NULL;
	data->args = NULL;
}

//start running minishell overlay
static void minishell(void)
{
	t_data *data;

	data = get_data();
	while (1)
	{
		printf("minishell> ");
		exit(0);
		//print prompt
		//init signal handling
		//readline
		//parse
		//execute
	}
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;

	init_data();
	minishell();
	exit_all();
	
	return (0);
}