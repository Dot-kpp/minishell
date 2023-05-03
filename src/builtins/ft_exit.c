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

//to be defined when architecture finished
//Free and clean
int	ft_exit(int argc, char const *argv[], t_list **envl)
{
	(void)argc;
	(void)argv;
	free_env(*envl);
	printf("Clean Exit\n");
	exit(0);
}
