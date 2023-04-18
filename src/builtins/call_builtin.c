/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:02:32 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/18 13:10:22 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ms_builtins.h"

typedef void	(*t_BuiltinFun) (int argc, char const *argv[], t_list **envl);

typedef struct s_builtin
{
	char			*name;
	t_BuiltinFun	fun;
}	t_builtin;

int	call_builtin(int argc, char const *argv[], t_list *envl)
{
	const t_builtin	builtins[] = {{"cd", ft_cd}, {"echo", ft_echo},
	{"env", ft_env}, {"exit", ft_exit}, {"export", ft_export},
	{"pwd", ft_pwd}, {"unset", ft_unset}};
	int				i;
	int				len;

	i = -1;
	while (++i < 7)
	{
		len = ft_strlen(builtins[i].name) + 1;
		if (!ft_strncmp(argv[1], builtins[i].name, len))
		{
			builtins[i].fun(argc - 1, argv + 1, &envl);
			return (1);
		}
	}
	return (0);
}
