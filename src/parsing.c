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

char	**cmd_split(char const *s)
{
	char	**tab;
	char	*str;
	char	*temp;
	int		len;
	int		count;

	str = (char *)s;
	tab = ft_calloc(1, sizeof(*tab));
	if (!tab)
		return (perror("cmd_split: "), (char **) NULL);
	count = -1;
	while (1)
	{
		len = 0;
		while (ft_strchr(WHTSPACES, str[len]) && str[len])
			str++;
		while (str[len] != '|' && str[len])
		{
			if (nextquote(str + len) < 0)
				return (NULL);
			len += nextquote(str + len) + 1;
		}
		temp = ft_substr(str, 0, len);
		tab = expand_matrix((const char **)tab, temp);
		free(temp);
		if (!tab)
			return (perror("cmd_split: "), NULL);
		if (!str[len])
			return (tab);
		str += len + 1;
	}
	return (tab);
}

char	**redir_split(char const *s, t_mshell *mshell)
{
	char	**tab;
	char	*str;
	int		len;
	int		count;
	char	*temp;

	str = (char *)s;
	while (!ft_strchr("<>", *str) && *str)
		str++;
	tab = ft_calloc(1, sizeof(*tab));
	if (!tab)
		return (perror("redir_split: "), (char **) NULL);
	count = -1;
	while (*str)
	{
		len = 0;
		if (ft_strchr("<>", str[len]))
		{
			while (ft_strchr("<>", str[len]) && str[len])
				len++;
		}
		else
		{
			while (!ft_strchr("\t\n\v\f\r <>\0", str[len]) && str[len])
				len += nextquote(str + len) + 1;
		}
		arg_quotes(&temp, str, len, mshell);
		tab = expand_matrix((const char **)tab, temp);
		free(temp);
		if (!tab)
			return (perror("redir_split: "), NULL);
		while (ft_strchr(WHTSPACES, str[len]) && str[len])
			str++;
		str += len;
	}
	return (tab);
}

t_cmdtab	*tokenize(char const *prompt, t_mshell *mshell)
{
	t_cmdtab	*cmdtab;
	char		**cmdlines;
	int			i;

	cmdtab = ft_calloc(1, sizeof(t_cmdtab));
	if (!cmdtab)
		return (perror("tokenize"), NULL);
	cmdlines = cmd_split(prompt);
	cmdtab->cmdc = get_matrixlen((const char **)cmdlines);
	cmdtab->cmdv = ft_calloc(cmdtab->cmdc, sizeof(t_cmd));
	if (!cmdtab->cmdv)
		return (perror("tokenize"), NULL);
	i = -1;
	while (cmdlines[++i])
	{
		cmdtab->cmdv[i].argv = arg_split(cmdlines[i], mshell);
		if (!cmdtab->cmdv[i].argv)
			return (free_cmdtab(cmdtab), NULL);
		cmdtab->cmdv[i].argc = get_matrixlen((const char **)cmdtab->cmdv[i].argv);
		if (cmdtab->cmdv[i].argc == 0)
			return (printf("Error: empty pipe\n"), NULL);
		cmdtab->cmdv[i].redirs = redir_split(cmdlines[i], mshell);
		if (!cmdtab->cmdv[i].redirs)
			return (free_cmdtab(cmdtab), NULL);
		cmdtab->cmdv[i].redirc = get_matrixlen((const char **)cmdtab->cmdv[i].redirs);
	}
	free_matrix(cmdlines);
	return (cmdtab);
}
