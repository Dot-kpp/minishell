/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:26:00 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/21 15:08:31 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ms_builtins.h"

//del env_var by name
int	ms_unset(int argc, char const *argv[], t_mshell *mshell)
{
	char	*todel;

	if (argc != 2)
		return (printf("ft_unset: Too many arguments\n"), 1);
	if (!is_valid_envp(argv[1], ft_strlen(argv[1])))
		return (printf("ft_unset: %s: invalid parameter name\n", argv[1]), 1);
	todel = ft_strjoin(argv[1], "=");
	mshell->env = shrink_matrix((const char **)mshell->env, todel);
	free(todel);
	return (0);
}
