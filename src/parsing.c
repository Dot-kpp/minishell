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

char	**cmd_split(char const *s, char const sep, int const size)
{
	char	**tab;
	char	*str;
	int		len;
	int		count;

	str = (char *)s;
	tab = ft_calloc(size + 1, sizeof(*tab));
	if (!tab)
		return (perror("cmd_split: "), (char **) NULL);
	count = -1;
	while (++count < size)
	{
		len = 0;
		while (str[len] != sep && str[len])
			len += nextquote(str + len) + 1;
		tab[count] = ft_substr(str, 0, len);
		if (!tab[count])
			return (perror("cmd_split: "), freetab(tab, count));
		str += len + 1;
	}
	return (tab);
}

char	*rpl_envp(const char *str, int len, t_mshell *mshell)
{
	char	*newstr;
    char	*temp;
	int		i;

	newstr = ft_calloc(1, sizeof(char));
	if (!newstr)
		return (0);
	i = -1;
	while (++i < len)
	{
		if (str[i] == '$')
		{
			newstr = ft_append(newstr, str, i);
			str += i + 1;
			len -= i + 1;
			i = 0;
			if (str[i] == '?')
				newstr = ft_append(newstr, str, i);
			else
			{
				while (isalnum(str[i]) || str[i] == '_')
                	i++;
				temp = ft_substr(str, 0, i);
				if (ms_getenv(temp, (const char **)mshell->env))
					newstr = ft_append(newstr,
							ms_getenv(temp, (const char **)mshell->env),
							strlen(ms_getenv(temp, (const char **)mshell->env)));
				free(temp);
			}
			str += i;
			len -= i;
			i = -1;
		}
	}
	newstr = ft_append(newstr, str, len);
	return (newstr);	
}

char	*arg_expand(char const *str, int len, t_mshell *mshell)
{
	char	*arg;
	int		shift;
	int		i;

	arg = ft_calloc(1, sizeof(char));
	if (!arg)
		return (0);
	shift = 0;
	i = -1;
	while (++i < len - shift)
	{
		if (str[shift + i] == '\'' || str[shift + i] == '\"')
		{
			arg = ft_append(arg, rpl_envp(str + shift, i, mshell), PATH_MAX);
			shift += i;
			i = nextquote(str + shift);
			if (str[shift] == '\'')
				arg = ft_append(arg, str + shift + 1, i - 1);
			if (str[shift] == '\"')
				arg = ft_append(arg, rpl_envp(str + shift + 1, i - 1, mshell), PATH_MAX);
			shift += i + 1;
			i = -1;
		}
	}
	if (i <= len - shift)
		arg = ft_append(arg, rpl_envp(str + shift, i, mshell), PATH_MAX);
	return (arg);
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
		tab[count] = arg_expand(str, len, mshell);
		if (!tab[count])
			return (perror("arg_split: "), freetab(tab, count));
		str += len + 1;
	}
	return (tab);
}

int	setredir(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd->argc)
	{
		if (cmd->argv[i][0] == '<' || cmd->argv[i][0] == '>')
		{
			cmd->redirs = dup_matrix((const char **)cmd->argv + i);
			cmd->redirc = cmd->argc - i;
			j = i - 1;
			while (++j < cmd->argc)
			{
				free(cmd->argv[j]);
				cmd->argv[j] = 0;
			} // cmd->argv[i] = 0; //probleme pour free ?
			cmd->argc = i;
			return (i);
		}
		i++;
	}
	return (i);
}

t_cmdtab	*tokenize(char const *prompt, t_mshell *mshell)
{
	t_cmdtab	*cmdtab;
	char		**cmdlines;
	int			i;

	cmdtab = ft_calloc(1, sizeof(t_cmdtab));
	cmdtab->cmdc = smartcount(prompt, "|", 0);
	if (cmdtab->cmdc <= 0)
		return (NULL);
	cmdtab->cmdv = ft_calloc(cmdtab->cmdc, sizeof(t_cmd));
	cmdlines = cmd_split(prompt, '|', cmdtab->cmdc);
	i = -1;
	while (cmdlines[++i])
	{
		cmdtab->cmdv[i].argc = smartcount(cmdlines[i], WHTSPACES, 1);
		if (cmdtab->cmdv[i].argc == 0)
			return (printf("Error: empty pipe\n"), NULL);
		cmdtab->cmdv[i].argv = arg_split(cmdlines[i], WHTSPACES,
				cmdtab->cmdv[i].argc, mshell);	
		free(cmdlines[i]);
		setredir(cmdtab->cmdv + i);
	}
	free(cmdlines);
	return (cmdtab);
}
