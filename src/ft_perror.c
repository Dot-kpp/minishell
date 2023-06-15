/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:29:01 by fgeslin           #+#    #+#             */
/*   Updated: 2023/06/12 15:54:26 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdarg.h>

int	ft_perror(int count, ...)
{
	int		i;
	va_list	ap;

	ft_putstr_fd("mshell: ", 2);
	va_start(ap, count);
	i = 0;
	while (i < count)
	{
		ft_putstr_fd(va_arg(ap, char *), 2);
		ft_putchar_fd(' ', 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	va_end(ap);
	return (0);
}
