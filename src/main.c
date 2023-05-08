/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:08:47 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/20 13:08:47 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ms_builtins.h"

static int  get_argsize(char **arg)
{
	int i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

//start running minishell overlay
static void minishell(t_list **envl)
{
	t_data	*data;
	(void)	data;
	char	*input;
	char	cwd[PATH_MAX];
	char	**args;
	int		ret = 0;

	while (1) {
		// Print prompt
		cwd_check(cwd);

		// Read user input
		ft_strlcat(cwd, " % ", PATH_MAX);
		input = readline(cwd);

		// If input is NULL, user has pressed Ctrl-D or EOF has been reached
		if (input == NULL) {
			printf("\n");
			break;
		}

		// If input is empty, continue to next loop iteration
		if (ft_strlen(input) == 0) {
			free(input);
			continue;
		}

		// Add input to history
		add_history(input);

		// CHECK IF ASSIGNATION

		// CHECK IF BUILTIN
		args = ft_split(input, ' ');
		ret = call_builtin(get_argsize(args), (const char **)args, envl);
		if (ret != -1)
		{
			for (size_t i = 0; args[i]; i++)
				free(args[i]);
			free(args);
			free(input);
			continue;
		}
		start_piping(envl, args);

		// Create child process to execute command
		// pid_t pid = fork();
		// if (pid == -1)
		// {
		// 	perror("fork() error");
		// 	return;
		// }
		// else if (pid == 0)
		// {
		// 	// Child process
		// 	// char *args[] = {"/bin/sh", "-c", input, NULL};
		// 	execv(args[0], args);
		// 	perror("execv() error");
		// 	exit(1);
		// }
		// else
		// {
		// 	// Parent process
		// 	int status;
		// 	waitpid(pid, &status, 0);
		// }

		free(args);
		free(input);
	}

}

int main(int ac, char const **av, char const **envp)
{
	t_list	*envl;
	(void)ac;
	(void)av;

	envl = 0;
	init_env(envp, &envl);

	// init_data();
	minishell(&envl);
	exit_all();
	clear_history();

	free_env(envl);
	
	return (0);
}
