/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   #tester_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:34:40 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/07 11:42:09 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ms_builtins.h"

//TESTER
int	main(int argc, char const *argv[], char const *env[])
{
	char	*str;
	pid_t	pid;
	int		*ret;

	if (!ft_strncmp(argv[1], "cd", 3))
	{
		/* -- FT_CD -- */
		ft_cd(argc - 1, argv + 1);
		return (ft_pwd(1));
	}
	else if (!ft_strncmp(argv[1], "echo", 5))
	{
		/* -- FT_ECHO -- */
		ft_echo(argc - 1, argv + 1);
	}
	else if (!ft_strncmp(argv[1], "env", 4))
	{
		/* -- FT_ENV -- */
		ft_env(env);
	}
	else if (!ft_strncmp(argv[1], "exit", 5))
	{
		/* -- FT_EXIT -- */
		ft_exit(NULL, NULL);
	}
	else if (!ft_strncmp(argv[1], "export", 7))
	{
		/* -- FT_EXPORT -- */
		ft_export(argv + 1);
	}
	else if (!ft_strncmp(argv[1], "pwd", 4))
	{
		/* -- FT_PWD -- */
		return (ft_pwd(argc - 1));
	}
	else if (!ft_strncmp(argv[1], "unset", 6))
	{
		/* -- FT_UNSET -- */
		ft_unset(argv + 1);
	}
	else if (!ft_strncmp(argv[1], "exec", 6))
	{
		/* -- EXEC -- */
		pid = fork();
		if (!pid)
			execve(argv[2], (char *const *)argv + 2, (char *const *)env);
		else
			waitpid(pid, ret, 0);
		printf("ms still here\n");
	}
	else
	{
		str = ft_strnrpl(argv[1], argv[2], argv[3], 0);
		printf("%s.\n", str);
		free(str);
	}
}
