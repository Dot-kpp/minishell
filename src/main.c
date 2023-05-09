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
	int		ret = 0;

	data = get_data();
	while (1) {
		cwd_check(data->cwd);
		ft_strlcat(data->cwd, " % ", PATH_MAX);
		data->input = readline(data->cwd);
		// If input is NULL, user has pressed Ctrl-D or EOF has been reached
		if (data->input == NULL) {
			printf("\n");
			break;
		}
		// If input is empty, continue to next loop iteration
		if (ft_strlen(data->input) == 0) {
			free(data->input);
			continue;
		}
		// Add input to history
		add_history(data->input);

		// CHECK IF ASSIGNATION

		// CHECK IF BUILTIN
		data->args = ft_split(data->input, ' ');
		ret = call_builtin(get_argsize(data->args), (const char **)data->args, envl);
		if (ret != -1)
		{
			for (size_t i = 0; data->args[i]; i++)
				free(data->args[i]);
			free(data->args);
			free(data->input);
			continue;
		}
		start_piping(envl, data->args);

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
		// 	// char *data->args[] = {"/bin/sh", "-c", data->input, NULL};
		// 	execv(data->args[0], data->args);
		// 	perror("execv() error");
		// 	exit(1);
		// }
		// else
		// {
		// 	// Parent process
		// 	int status;
		// 	waitpid(pid, &status, 0);
		// }

		free(data->args);
		free(data->input);
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
