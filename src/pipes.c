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
#include <sys/ioctl.h>

#define IN 0
#define OUT 1

//child process
static void	exec_child(int i, int pfd[2][2], t_cmdtab *cmdtab, t_mshell *ms)
{
	int	ret;

	signal(SIGQUIT, SIG_ERR);
	signal(SIGINT, SIG_ERR);
	if (i > 0)
	{
		dup2(pfd[1][0], STDIN_FILENO);
		close(pfd[1][0]);
		close(pfd[1][1]);
	}
	if (i < cmdtab->cmdc - 1)
		dup2(pfd[0][1], STDOUT_FILENO);
	close(pfd[0][0]);
	close(pfd[0][1]);
	ret = call_redirections(&cmdtab->cmdv[i]);
	if (ret)
		exit(ret);
	ret = exec_cmd(cmdtab->cmdv[i], ms);
	free_cmdtab(cmdtab);
	free_matrix(ms->env);
	exit(ret);
}

//main process
static void	close_pipes(int i, int pipefd[2], int ppipefd[2], t_cmdtab *cmdtab)
{
	if (i > 0)
	{
		close(ppipefd[0]);
		close(ppipefd[1]);
	}
	if (i < cmdtab->cmdc - 1)
	{
		ppipefd[0] = pipefd[0];
		ppipefd[1] = pipefd[1];
	}
	if (i == cmdtab->cmdc - 1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

static int	pipeline(t_cmdtab *cmdtab, t_mshell *mshell,
		pid_t *pids, int pipesfd[2][2])
{
	int	exit_status;
	int	i;

	i = -1;
	while (++i < cmdtab->cmdc)
	{
		exit_status = try_builtin(cmdtab, mshell, i);
		if (exit_status > -1)
			return (free(pids), exit_status);
		if (pipe(pipesfd[0]) == -1)
			return (perror("pipe"), EXIT_FAILURE);
		pids[i] = fork();
		if (pids[i] == -1)
			return (perror("fork"), EXIT_FAILURE);
		else if (pids[i] == 0)
		{
			free(pids);
			exec_child(i, pipesfd, cmdtab, mshell);
		}
		close_pipes(i, pipesfd[0], pipesfd[1], cmdtab);
	}
	return (-1);
}

int	exec_pipeline(t_cmdtab *cmdtab, t_mshell *mshell)
{
	int		exit_status;
	pid_t	*pids;
	int		i;
	int		pipesfd[2][2];

	signal(SIGINT, SIG_IGN);
	pipesfd[0][0] = 0;
	pipesfd[0][1] = 1;
	pipesfd[1][0] = -1;
	pipesfd[1][1] = -1;
	pids = ft_calloc(cmdtab->cmdc + 1, sizeof(int));
	if (pids == NULL)
		return (perror("exec"), EXIT_FAILURE);
	exit_status = pipeline(cmdtab, mshell, pids, pipesfd);
	if (exit_status > -1)
		return (exit_status);
	i = -1;
	while (++i < cmdtab->cmdc)
		waitpid(pids[i], &exit_status, 0);
	free(pids);
	return (WEXITSTATUS(exit_status));
}
