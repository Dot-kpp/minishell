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

typedef int	(*t_BuiltinFun) (int argc, char const *argv[], t_list **envl);

typedef struct s_builtin
{
	char			*name;
	t_BuiltinFun	fun;
}	t_builtin;

int	call_builtin(int argc, char const *argv[], t_list **envl)
{
	const t_builtin	builtins[] = {
	{"cd", ft_cd},
	{"echo", ft_echo},
	{"env", ft_env},
	{"exit", ft_exit},
	{"export", ft_export},
	{"pwd", ft_pwd},
	{"unset", ft_unset}};
	int				i;
	int				len;

	i = -1;
	while (++i < 7)
	{
		len = ft_strlen(builtins[i].name) + 1;
		if (!ft_strncmp(argv[0], builtins[i].name, len))
			return (builtins[i].fun(argc, argv, envl));
	}
	return (-1);
}
