/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:23:01 by fgeslin           #+#    #+#             */
/*   Updated: 2023/06/01 17:08:43 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ms_builtins.h"

// to be called only if '/' in the cmd
char	*expand_cmd(char *name, char *path)
{
	char	**paths;
	char	*temp_path;
	int		len;
	int		i;

	paths = ft_split((const char *)path, ':');
	len = 0;
	while (paths[len])
		len++;
	i = 0;
	while (i < len)
	{
		temp_path = ft_strdup(paths[i]);
		temp_path = ft_append(temp_path, "/", 2);
		temp_path = ft_append(temp_path, name, ft_strlen(name) + 1);
		if (access(temp_path, F_OK) == 0)
			return (freetab(paths, len), temp_path);
		free(temp_path);
		i++;
	}
	return (freetab(paths, len), name);
}

int	exec_cmd(t_cmd cmd, t_mshell *mshell)
{
	int		exit_status;
	pid_t	pid;

	exit_status = call_builtin(cmd.argc, (const char **)cmd.argv, mshell);
	if (exit_status > -1)
		return (exit_status);
	pid = fork();
	if (pid == 0)
	{
		exit_status = execve(expand_cmd(cmd.argv[0], ms_getenv("PATH",
						(const char **)mshell->env)), cmd.argv, mshell->env);
		// printf("fork %d\n", exit_status);
		if (exit_status > -1)
			exit (exit_status);
		// printf("command not found: %s\n", cmd.argv[0]);
		exit (-1);
	}
	else
	{
		waitpid(pid, &exit_status, 0);
		// printf("mainwait %d\n", WEXITSTATUS(exit_status));
		return (WEXITSTATUS(exit_status));
	}
}
