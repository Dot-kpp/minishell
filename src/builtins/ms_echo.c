/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:26:29 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/19 12:39:23 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	checkflag(const char *str)
{
	int	i;

	i = 1;
	while (str[i] == 'n')
		i++;
	if (i == (int)ft_strlen(str))
		return (1);
	return (0);
}

//Output to be defined
int	ms_echo(int argc, char const *argv[], t_mshell *mshell)
{
	int	i;
	int	newline;

	(void)mshell;
	i = 0;
	newline = 1;
	while (++i < argc)
	{
		if (i == 1 && !ft_strncmp(argv[1], "-n", 2))
		{
			if (checkflag(argv[1]))
			{
				newline = 0;
				continue ;
			}
		}
		printf("%s", argv[i]);
		if (i + 1 < argc)
			printf(" ");
	}
	if (newline)
		printf("\n");
	return (0);
}
