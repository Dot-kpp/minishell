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
