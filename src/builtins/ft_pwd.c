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
int	ft_pwd(int argc, char const *argv[], t_list **envl)
{
	char	cwd[PATH_MAX];

	(void)argv;
	(void)envl;
	if (argc > 1)
		perror("pwd: too many arguments");
	else if (getcwd(cwd, PATH_MAX) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
		perror("pwd:");
	return (1);
}
