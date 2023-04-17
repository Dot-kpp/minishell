/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:59:56 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/11 14:43:19 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>

//pad de fork/execv pour call cd (tout les builtins ?)

//Does not support natively $, ~, ' and " (must be handled before)
//argc == 3 not supported (not asked)
//Output to be defined
void	ft_cd(int argc, char const *argv[])
{
	int		err;
	char	*path;
	char	*home;

	home = getenv("HOME");
	if (!home && argc == 1)
		return ;
	path = (char *)argv[1];
	if (argc > 2)
		perror("ft_cd: too many args");
	if (argc == 1 && home)
		err = chdir(home);
	else if (!path[0] || !home)
		return ;
	else
		err = chdir(path);
	if (err)
	{
		perror("ft_cd");
		exit (1);
	}
}
