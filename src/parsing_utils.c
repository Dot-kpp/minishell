/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:18:20 by fgeslin           #+#    #+#             */
/*   Updated: 2023/05/24 12:21:41 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nextquote(char const *s)
{
	int	i;

	i = 0;
	if (*s == '\'' || *s == '\"')
	{
		while (s[++i])
		{
			if (s[i] == *s)
				return (i);
		}
		return (perror("QUOTE_ERR"), -1);
	}
	return (0);
}

int	smartcount(char const *s, char const *sep, int trim_sep)
{
	int		count;
	char	*str;

	if (trim_sep)
		count = 0;
	else
		count = 1;
	str = (char *)s;
	while (*str)
	{
		if (nextquote(str) >= 0)
			str += nextquote(str);
		else
			return (-1);
		if (trim_sep)
		{
			if (!ft_strchr(sep, *str) && ft_strchr(sep, *(str + 1)))
				count++;
		}
		else if (ft_strchr(sep, *str))
			count++;
		str++;
	}
	return (count);
}
