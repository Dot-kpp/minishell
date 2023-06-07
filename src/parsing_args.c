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
#include "../includes/ms_builtins.h"

int	arg_expand2(char **s, const char *str, t_mshell *mshell)
{
	char	*temp;
	int		i;

	i = 0;
	if (str[i] == '?')
	{
		i++;
		*s = ft_append(*s, ft_itoa((int)mshell->exit_status),
				ft_strlen(ft_itoa((int)mshell->exit_status)));
	}
	else
	{
		while (isalnum(str[i]) || str[i] == '_')
			i++;
		temp = ft_substr(str, 0, i);
		if (ms_getenv(temp, (const char **)mshell->env))
			*s = ft_append(*s,
					ms_getenv(temp, (const char **)mshell->env),
					strlen(ms_getenv(temp, (const char **)mshell->env)));
		free(temp);
	}
	return (i);
}

char	*arg_expand(char *s, const char *str, int len, t_mshell *mshell)
{
	int		i;

	i = -1;
	while (++i < len)
	{
		if (str[i] != '$')
			continue ;
		s = ft_append(s, str, i);
		str += i + 1;
		len -= i + 1;
		i = arg_expand2(&s, str, mshell);
		str += i;
		len -= i;
		i = -1;
	}
	s = ft_append(s, str, len);
	return (s);
}

int	arg_quotes(char **arg, char const *str, int len, t_mshell *mshell)
{
	int		shift;
	int		i;

	*arg = ft_calloc(1, sizeof(char));
	if (!*arg)
		return (0);
	shift = 0;
	i = -1;
	while (++i < len - shift)
	{
		if (!(str[shift + i] == '\'' || str[shift + i] == '\"'))
			continue ;
		*arg = arg_expand(*arg, str + shift, i, mshell);
		shift += i;
		i = nextquote(str + shift);
		if (str[shift] == '\'')
			*arg = ft_append(*arg, str + shift + 1, i - 1);
		if (str[shift] == '\"')
			*arg = arg_expand(*arg, str + shift + 1, i - 1, mshell);
		shift += i + 1;
		i = -1;
	}
	if (i <= len - shift)
		*arg = arg_expand(*arg, str + shift, i, mshell);
	return (1);
}

char	**arg_split(char const *s, char const *sep, int size, t_mshell *mshell)
{
	char	**tab;
	char	*str;
	int		len;
	int		count;

	str = (char *)s;
	tab = ft_calloc(size + 1, sizeof(*tab));
	if (!tab)
		return (perror("arg_split: "), (char **)0);
	count = -1;
	while (++count < size)
	{
		len = 0;
		while (ft_strchr(sep, str[len]) && *str)
			str++;
		while (!ft_strchr(sep, str[len]) && str[len])
			len += nextquote(str + len) + 1;
		arg_quotes(tab + count, str, len, mshell);
		if (!tab[count])
			return (perror("arg_split: "), freetab(tab, count));
		str += len + 1;
	}
	return (tab);
}
