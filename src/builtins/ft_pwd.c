/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:49:06 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/18 11:53:42 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

// Input / Output to be defined
void	ft_pwd(int argc, char const *argv[], t_list **envl)
{
	char	cwd[PATH_MAX];

	(void)argv;
	(void)envl;
	if (argc > 1)
		perror("pwd: too many arguments");
	else if (getcwd(cwd, PATH_MAX) != NULL)
	{
		printf("%s\n", cwd);
		return ;
	}
	else
		perror("pwd:");
	exit (1);
}
