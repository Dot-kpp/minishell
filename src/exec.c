/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:23:01 by fgeslin           #+#    #+#             */
/*   Updated: 2023/06/02 13:51:00 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ms_builtins.h"

char	*expand_cmd(char *name, char *path)
{
	char	**paths;
	char	*temp_path;
	int		len;
	int		i;

	if (ft_strchr(name, '/'))
		return (name);
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
	return (freetab(paths, len), NULL);
}

int	is_funnofork(t_cmd cmd)
{
	if (!ft_strncmp(cmd.argv[0], "cd", 3))
		return (1);
	if (!ft_strncmp(cmd.argv[0], "exit", 5))
		return (1);
	if (!ft_strncmp(cmd.argv[0], "unset", 6))
		return (1);
	if (!ft_strncmp(cmd.argv[0], "export", 7) && cmd.argc > 1)
		return (1);
	return (0);
}

int exec_cmd(t_cmd cmd, t_mshell *mshell)
{
    int exit_status;
    pid_t pid;

	// if (ft_strncmp(cmd.argv[0], "|", 2) == 0) {
    // 	exit_status = exec_pipeline(&cmd.argc, (char **)cmd.argv , mshell);
    //     if (exit_status > -1)
    //         return exit_status;
    // }

		// call_redirections(&cmd, mshell);
	// if (ft_strncmp(cmd.argv[0], "cd", 3) == 0 || ft_strncmp(cmd.argv[0], "echo", 5) == 0 || ft_strncmp(cmd.argv[0], "exit", 5) == 0 || ft_strncmp(cmd.argv[0], "export", 7) == 0 || ft_strncmp(cmd.argv[0], "unset", 6) == 0) {
    if (is_funnofork(cmd))
	{
		exit_status = call_builtin(cmd.argc, (const char **)cmd.argv, mshell);
        if (exit_status > -1)
            return exit_status;
    }
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
		call_redirections(&cmd, mshell);
		exit_status = call_builtin(cmd.argc, (const char **)cmd.argv, mshell);
        if (exit_status > -1)
            exit (exit_status);
        exit_status = execve(expand_cmd(cmd.argv[0],
				ms_getenv("PATH", (const char **)mshell->env)), cmd.argv, mshell->env);
        if (exit_status > -1)
            exit(exit_status);
		printf("mshell: command not found: %s\n", cmd.argv[0]);
        exit(EXIT_FAILURE);
    } else {
        waitpid(pid, &exit_status, 0);
        return WEXITSTATUS(exit_status);
    }
}
