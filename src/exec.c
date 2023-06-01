/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:23:01 by fgeslin           #+#    #+#             */
/*   Updated: 2023/06/01 16:41:48 by fgeslin          ###   ########.fr       */
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
	int		ret;
	pid_t	pid;

	ret = call_builtin(cmd.argc, (const char **)cmd.argv, mshell);
	if (ret > -1)
		return (ret);
	pid = fork();
	if (pid == 0)
	{
		ret = execve(expand_cmd(cmd.argv[0], ms_getenv("PATH",
						(const char **)mshell->env)), cmd.argv, mshell->env);
		if (ret > -1)
			exit (ret);
		printf("command not found: %s\n", cmd.argv[0]);
		exit (-1);
	}
	else
	{
		waitpid(pid, &ret, 0);
		return (ret);
	}
}
