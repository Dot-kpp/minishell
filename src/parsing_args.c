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

int	endofarg(const char *str, int i)
{
	if (str[i] >= '0' && str[i] <= '9')
	{
		while (str[i] >= '0' && str[i] <= '9')
			i++;
	}
	else
	{
		while (isalnum(str[i]) || str[i] == '_')
			i++;
	}
	return (i);
}

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
	else if (ft_isalnum(str[i]) || str[i] == '_')
	{
		i = endofarg(str, i);
		temp = ft_substr(str, 0, i);
		if (ms_getenv(temp, (const char **)mshell->env))
			*s = ft_append(*s,
					ms_getenv(temp, (const char **)mshell->env),
					strlen(ms_getenv(temp, (const char **)mshell->env)));
		free(temp);
	}
	else
		*s = ft_append(*s, "$", 2);
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

char	*arg_quotes(char const *str, int len, t_mshell *mshell)
{
	int		i[2];
	char	*arg;

	arg = ft_calloc(1, sizeof(char));
	if (!arg)
		return (NULL);
	i[0] = -1;
	i[1] = 0;
	while (++i[0] < len - i[1])
	{
		if (!(str[i[1] + i[0]] == '\'' || str[i[1] + i[0]] == '\"'))
			continue ;
		arg = arg_expand(arg, str + i[1], i[0], mshell);
		i[1] += i[0];
		i[0] = nextquote(str + i[1]);
		if (str[i[1]] == '\'')
			arg = ft_append(arg, str + i[1] + 1, i[0] - 1);
		if (str[i[1]] == '\"')
			arg = arg_expand(arg, str + i[1] + 1, i[0] - 1, mshell);
		i[1] += i[0] + 1;
		i[0] = -1;
	}
	if (i[0] <= len - i[1])
		arg = arg_expand(arg, str + i[1], i[0], mshell);
	return (arg);
}
