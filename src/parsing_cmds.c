/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:07:46 by jpilotte          #+#    #+#             */
/*   Updated: 2023/05/23 16:21:07 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	cmd_split2(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '|' && str[i])
	{
		if (nextquote(str + i) < 0)
			return (-1);
		i += nextquote(str + i) + 1;
	}
	return (i);
}

char	**cmd_split(char const *s)
{
	char	**tab;
	char	*str;
	int		len;

	str = (char *)s;
	tab = ft_calloc(1, sizeof(*tab));
	if (!tab)
		return (perror("cmd_split: "), NULL);
	while (1)
	{
		while (ft_strchr(WHTSPACES, str[0]) && str[0])
			str++;
		len = cmd_split2(str);
		if (len == -1)
			return (ft_perror(1, "quote error"), NULL);
		tab = expand_matrix((MATRIX)tab, ft_substr(str, 0, len));
		if (!tab)
			return (perror("cmd_split: "), NULL);
		if (!str[len])
			return (tab);
		str += len + 1;
	}
	return (tab);
}
