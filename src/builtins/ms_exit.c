/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:52:51 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/19 12:39:30 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ms_builtins.h"

//Free and clean
int	ms_exit(int argc, char const *argv[], t_mshell *mshell)
{
	int	ret;

	ret = 0;
	if (argc > 2)
		return (ft_perror(1, "exit: too many arguments"), 1);
	else if (argc == 2)
		ret = ft_atoi(argv[1]);
	(void)*mshell;
	printf("exit\n");
	exit(ret);
}
