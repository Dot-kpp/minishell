/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:49:06 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/06 12:07:42 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

// Input / Output to be defined
int	ft_pwd(int argc)
{
	char	cwd[PATH_MAX];

	if (argc > 1)
		return (perror("🔴 pwd: too many arguments"), 1);
	else if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (printf("%s\n", cwd), 0);
	else
		return (perror("🔴 pwd: getcwd() failed"), 1);
}
