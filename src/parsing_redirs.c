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

int	redir_split2(char *str)
{
	int	i;

	i = 0;
	if (ft_strchr("<>", str[i]))
	{
		while (ft_strchr("<>", str[i]) && str[i])
			i++;
		if (ft_strncmp(str, ">", i) && ft_strncmp(str, ">>", i)
			&& ft_strncmp(str, "<", i) && ft_strncmp(str, "<<", i))
			return (printf("mshell: parse error near '%c'\n", *str), -1);
	}
	else
	{
		while (!ft_strchr("\t\n\v\f\r <>\0", str[i]) && str[i])
			i += nextquote(str + i) + 1;
	}
	return (i);
}

char	**redir_split(char const *s, t_mshell *mshell)
{
	char	**tab;
	char	*str;
	int		len;

	str = (char *)s;
	while (!ft_strchr("<>", *str) && *str)
		str += nextquote(str) + 1;
	tab = ft_calloc(1, sizeof(*tab));
	if (!tab)
		return (perror("redir_split: "), (char **) NULL);
	while (*str)
	{
		len = redir_split2(str);
		if (len == -1)
			return (NULL);
		tab = expand_matrix((MATRIX)tab, arg_quotes(str, len, mshell));
		if (!tab)
			return (perror("redir_split: "), NULL);
		while (ft_strchr(WHTSPACES, str[len]) && str[len])
			str++;
		str += len;
	}
	return (tab);
}
