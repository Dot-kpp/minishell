/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:26:29 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/18 11:53:01 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Output to be defined
void	ft_echo(int argc, char const *argv[], t_list **envl)
{
	int	i;
	int	newline;

	(void)envl;
	i = 0;
	newline = 1;
	while (++i < argc)
	{
		if (i == 1 && !strcmp(argv[1], "-n"))
		{
			newline = 0;
			continue ;
		}
		printf("%s", argv[i]);
		if (i + 1 < argc)
			printf(" ");
	}
	if (newline)
		printf("\n");
}
