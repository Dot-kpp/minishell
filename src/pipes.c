/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:08:45 by jpilotte          #+#    #+#             */
/*   Updated: 2023/05/09 13:12:24 by jpilotte         ###   ########.fr       */
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

void start_piping(t_list **envl, t_data *data)
{
		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork() error");
			return;
		}
		else if (pid == 0)
		{
			// Child process
            char *args[] = {"/bin/sh", "-c", data->input, NULL};
            data->args = args;
			if (execv(data->args[0], data->args) == -1) 
            {
                perror("execv() error");
                exit(1);
            }
            call_builtin(get_argsize(args), (const char **)args, envl);
		}
        else
        {
        // Parent process
            int status;
            if (waitpid(pid, &status, 0) == -1) 
            {
                perror("waitpid() error");
            }
        }
}