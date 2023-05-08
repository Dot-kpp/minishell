/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:08:45 by jpilotte          #+#    #+#             */
/*   Updated: 2023/05/08 12:11:34 by jpilotte         ###   ########.fr       */
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

void start_piping(t_list **envl, char **args)
{
    int		i;
    int		fd[2];
    int		fd_in;
    pid_t	pid;

    i = 0;
    fd_in = 0;
    while (args[i])
    {
        pipe(fd);
        pid = fork();
        if (pid == 0)
        {
            dup2(fd_in, 0);
            if (args[i + 1])
                dup2(fd[1], 1);
            close(fd[0]);
            call_builtin(get_argsize(args), (const char **)args, envl);
            exit(0);
        }
        else
        {
            wait(NULL);
            close(fd[1]);
            fd_in = fd[0];
            i++;
        }
    }
}