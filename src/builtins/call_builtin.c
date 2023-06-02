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
	char			*fun;
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
		fun = (char *)argv[0];
		len = -1;
		while (argv[0][++len])
			fun[len] = ft_tolower(argv[0][len]);
		len = ft_strlen(builtins[i].name) + 1;
		if (!ft_strncmp(fun, builtins[i].name, len))
			return (builtins[i].fun(argc, argv, mshell));
	}
	return (-1);
}
