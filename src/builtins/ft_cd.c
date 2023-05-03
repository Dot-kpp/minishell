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

//Does not support natively $, ~, ' and " (must be handled before)
//argc == 3 not supported (not asked)
int	ft_cd(int argc, char const *argv[], t_list **envl)
{
	int		err;
	char	*home;

	(void)envl;
	home = get_envp(*envl, "HOME");
	if (argc > 2)
		return (printf("ft_cd: Too many args\n"), 1);
	else if (argc == 1)
	{
		if (home)
			err = chdir(home);
		else
			return (0);
	}
	else
		err = chdir(argv[1]);
	if (err)
		return (perror("ft_cd"), 1);
	return (0);
}
