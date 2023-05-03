/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   #tester_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:34:40 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/18 12:32:47 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ms_builtins.h"

//TESTER
int	main(int argc, char const *argv[], char const *env[])
{
	t_list	*envl;
	pid_t	pid;
	int		*ret;

	ret = NULL;
	envl = NULL; // init error
	init_env(env, &envl);

	//if assigantion
	//	do assignation
	//else
	if (call_builtin(argc, argv, envl))
		ret = 0;
	else //check if starts by "./" ?
	{
		/* -- EXEC -- */
		pid = fork();
		if (!pid)
		{
			//envl to array
			execve(argv[1], (char *const *)argv + 1, (char *const *)env);
			perror("execve: ");
			exit(1);
		}
		else
			waitpid(pid, ret, 0);
		printf("ms still here\n");
	}
	
	free_env(envl);
	return (ret);
}
