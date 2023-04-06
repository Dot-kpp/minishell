/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:52:51 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/06 12:07:59 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//to be defined when architecture finished
//Free and clean
void	ft_exit(void f(void*), void *param)
{
	if (f)
		f(param);
	exit(0);
}
