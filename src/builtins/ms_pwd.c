/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:49:06 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/19 12:39:54 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

// Input / Output to be defined
int	ms_pwd(int argc, char const *argv[], t_mshell *mshell)
{
	char	cwd[PATH_MAX];

	(void)argc;
	(void)argv;
	(void)mshell;
	if (getcwd(cwd, PATH_MAX) != NULL)
		return (printf("%s\n", cwd), 0);
	else
		perror("pwd:");
	return (1);
}
