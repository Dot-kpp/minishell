/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:23:01 by fgeslin           #+#    #+#             */
/*   Updated: 2023/05/29 14:34:56 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ms_builtins.h"

// called only if '/' in the cmd
char	*expand_cmd(char *name, t_list *envl)
{
	char	**paths;
	char	*temp_path;
	int		len;
	int		i;

	paths = ft_split((const char *)get_envp(envl, "PATH"), ':');
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

int exec_cmd(t_cmd cmd, t_list **envl)
{
	int		ret;
	pid_t	pid;

	ret = call_builtin(cmd.argc, (const char **)cmd.argv, envl);
	if (ret > -1)
		return (ret);

	pid = fork();
	if (pid == 0)
	{
		ret = execve(expand_cmd(cmd.argv[0], *envl), cmd.argv, NULL); //envl to char *const*
		if (ret > -1)
			return (ret);
		return (printf("command not found: %s\n", cmd.argv[0]), -1);
	}
	else
	{
		waitpid(pid, &ret, 0);
		return(ret);
	}
}
