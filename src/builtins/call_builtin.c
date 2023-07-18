/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:02:32 by fgeslin           #+#    #+#             */
/*   Updated: 2023/05/08 10:52:51 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ms_builtins.h"

typedef int	(*t_BuiltinFun) (int argc, char const *argv[], t_mshell *mshell);

typedef struct s_builtin
{
	char			*name;
	t_BuiltinFun	fun;
}	t_builtin;

int	call_builtin(int argc, char const *argv[], t_mshell *mshell)
{
	char			*lower_arg;
	const t_builtin	builtins[] = {
	{"cd", ms_cd},
	{"echo", ms_echo},
	{"env", ms_env},
	{"exit", ms_exit},
	{"export", ms_export},
	{"pwd", ms_pwd},
	{"unset", ms_unset}};
	int				i;
	int				len;

	i = -1;
	while (++i < 7)
	{
		lower_arg = ft_strdup(argv[0]);
		len = -1;
		while (argv[0][++len])
			lower_arg[len] = ft_tolower(argv[0][len]);
		len = ft_strlen(builtins[i].name) + 1;
		if (!ft_strncmp(lower_arg, builtins[i].name, len))
			return (free(lower_arg), builtins[i].fun(argc, argv, mshell));
		free(lower_arg);
	}
	return (-1);
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

int	try_builtin(t_cmdtab *cmdtab, t_mshell *mshell, int i)
{
	int	exit_status;

	exit_status = -1;
	if (cmdtab->cmdv[i].argv[0] && is_funnofork(cmdtab->cmdv[i])
		&& cmdtab->cmdc == 1)
	{
		exit_status = call_builtin(cmdtab->cmdv[i].argc,
				(t_mat)cmdtab->cmdv[i].argv, mshell);
	}
	return (exit_status);
}
