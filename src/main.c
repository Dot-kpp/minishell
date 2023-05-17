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

int execute_command(char *command) {
    // Fork a child process to execute the command
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork() error");
        return -1;
    } else if (pid == 0) {
        // Child process
        execlp("/bin/sh", "sh", "-c", command, NULL);
        perror("execlp() error");
        exit(1);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            // Handle abnormal termination
            return -1;
        }
    }
}

void check_if_exit(void)
{
	t_data *data;

	data = get_data();
	int exit_status = execute_command(data->input);
    if (exit_status != -1) {
        data->previous_exit_status = exit_status;
        printf("Exit status: %d\n", exit_status);
    }
}

//start running minishell overlay
static void minishell(t_list **envl)
{
	t_data	*data;
	int		ret = 0;

	data = get_data();
	while (1) {
		cwd_check(data->cwd);
		ft_strlcat(data->cwd, "\001\033[1;96m\002 % \033[0;39m\001", PATH_MAX);
		new_prompt_signal();
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

		// CHECK IF EXIT with $? = exit_status
		check_if_exit();
		// CHECK IF ASSIGNATION
		
		// CHECK IF BUILTIN
		data->args = ft_split(data->input, ' ');
		ret = call_builtin(get_argsize(data->args), (const char **)data->args, envl);
		if (ret != -1)
		{
			for (size_t i = 0; data->args[i]; i++)
				free(data->args[i]);
			free_input();
			continue;
		}
		start_piping(envl, data);
		free_input();
	}
}

int main(int ac, char const **av, char const **envp)
{
	t_list	*envl;
	(void)ac;
	(void)av;

	envl = 0;
	init_env(envp, &envl);
	init_data();
	minishell(&envl);
	exit_all();
	clear_history();

	free_env(envl);
	
	return (0);
}
