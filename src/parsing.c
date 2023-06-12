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

static int	init_tokenize(char const *prompt, t_cmdtab **tct, char ***cl)
{
	t_cmdtab	*cmdtab;
	char		**cmdlines;

	cmdtab = ft_calloc(1, sizeof(t_cmdtab));
	if (!cmdtab)
		return (perror("mshell"), 1);
	cmdlines = cmd_split(prompt);
	if (!cmdlines)
		return (perror("mshell"), 1);
	cmdtab->cmdc = get_matrixlen((MATRIX)cmdlines);
	cmdtab->cmdv = ft_calloc(cmdtab->cmdc, sizeof(t_cmd));
	if (!cmdtab->cmdv)
		return (perror("mshell"), 1);
	*tct = cmdtab;
	*cl = cmdlines;
	return (0);
}

t_cmdtab	*tokenize(char const *prompt, t_mshell *mshell)
{
	t_cmdtab	*cmdtab;
	char		**cmdlines;
	int			i;

	if (init_tokenize(prompt, &cmdtab, &cmdlines))
		return (NULL);
	i = -1;
	while (cmdlines[++i])
	{
		cmdtab->cmdv[i].argv = arg_split(cmdlines[i], mshell);
		if (!cmdtab->cmdv[i].argv)
			return (free_cmdtab(cmdtab), NULL);
		cmdtab->cmdv[i].argc = get_matrixlen((MATRIX)cmdtab->cmdv[i].argv);
		if (cmdtab->cmdv[i].argc == 0)
			return (ft_perror(1, "parse error near '|'"), NULL);
		cmdtab->cmdv[i].redirs = redir_split(cmdlines[i], mshell);
		if (!cmdtab->cmdv[i].redirs)
			return (free_cmdtab(cmdtab), NULL);
		cmdtab->cmdv[i].redirc = get_matrixlen((MATRIX)cmdtab->cmdv[i].redirs);
	}
	free_matrix(cmdlines);
	return (cmdtab);
}
