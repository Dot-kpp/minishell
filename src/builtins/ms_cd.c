/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:59:56 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/20 11:21:46 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ms_builtins.h"

static void	updatepwd(char oldpwd[PATH_MAX], t_mshell *mshell)
{
	char	envvar[PATH_MAX];

	ft_strlcpy(envvar, "OLDPWD=", PATH_MAX);
	ft_strlcat(envvar, oldpwd, PATH_MAX);
	update_envp(envvar, mshell);
	getcwd(oldpwd, PATH_MAX);
	ft_strlcpy(envvar, "PWD=", PATH_MAX);
	ft_strlcat(envvar, oldpwd, PATH_MAX);
	update_envp(envvar, mshell);
}

int	ms_cd(int argc, char const *argv[], t_mshell *mshell)
{
	int		err;
	char	*home;
	char	oldpwd[PATH_MAX];

	err = 0;
	getcwd(oldpwd, PATH_MAX);
	if (argc > 2)
		return (printf("ft_cd: Too many args\n"), 1);
	else if (argc == 1)
	{
		home = ms_getenv("HOME", (const char **)mshell->env);
		if (home)
			err = chdir(home);
	}
	else
		err = chdir(argv[1]);
	if (err)
		return (perror("ft_cd"), 1);
	updatepwd(oldpwd, mshell);
	return (0);
}
