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

#define IN 0
#define OUT 1

static void	init_var(int *exit_status, int *ppipefd1, int *ppipefd2, int *i)
{
	*exit_status = 0;
	*ppipefd1 = -1;
	*ppipefd2 = -1;
	*i = -1;
}

static int	init_pipes(int i, int pipefd[2], t_cmdtab *cmdtab)
{
	if (i < cmdtab->cmdc - 1)
	{
		if (pipe(pipefd) == -1)
			return (perror("pipe"), EXIT_FAILURE);
	}
	return (0);
}

static void	dup_pipes(int i, int pipefd[2], int ppipefd[2], t_cmdtab *cmdtab)
{
	if (i > 0)
	{
		dup2(ppipefd[0], STDIN_FILENO);
		close(ppipefd[0]);
		close(ppipefd[1]);
	}
	if (i < cmdtab->cmdc - 1)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

static void	close_pipes(int i, int pipefd[2], int ppipefd[2], t_cmdtab *cmdtab)
{
	if (ppipefd[0] != -1)
	{
		close(ppipefd[0]);
		close(ppipefd[1]);
	}
	if (i < cmdtab->cmdc - 1)
	{
		ppipefd[0] = pipefd[0];
		ppipefd[1] = pipefd[1];
	}
}

int	exec_pipeline(t_cmdtab *cmdtab, t_mshell *mshell)
{
	int		exit_status;
	pid_t	pid;
	int		i;
	int		pipesfd[2][2];

	init_var(&exit_status, &pipesfd[IN][0], &pipesfd[IN][1], &i);
	while (++i < cmdtab->cmdc)
	{
		if (init_pipes(i, pipesfd[0], cmdtab))
			return (EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			dup_pipes(i, pipesfd[IN], pipesfd[OUT], cmdtab);
			exit(exec_cmd(cmdtab->cmdv[i], mshell));
		}
		close_pipes(i, pipesfd[IN], pipesfd[OUT], cmdtab);
		waitpid(pid, &exit_status, 0);
	}
	return (WEXITSTATUS(exit_status));
}
