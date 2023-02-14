#include "../includes/minishell.h"



void read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	getline(&line, &bufsize, stdin);
	return (line);
}

int main(int argc, char **argv, char **envp)
{
	char *line;
	char **args;
	int status;

	while (1)
	{
		printf("minishell$ ");
		line = read_line();
		args = split_line(line);
		status = execute(args);

		free(line);
		free(args);
	}
	return (0);
}
