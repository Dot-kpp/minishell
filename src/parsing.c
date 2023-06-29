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

static char	**arg_addtomat(const char **tab, char **str, t_mshell *mshell)
{
	int		len;
	char	**new_tab;

	len = 0;
	while (!ft_strchr("\t\n\v\f\r <>\0", (*str)[len]) && (*str)[len])
		len += nextquote((*str) + len) + 1;
	new_tab = expand_matrix(tab, arg_quotes((*str), len, mshell));
	if (!new_tab)
		return (perror("cmd_split: "), NULL);
	while (ft_strchr(WHTSPACES, (*str)[len]) && (*str)[len])
		(*str)++;
	(*str) += len;
	return (new_tab);
}

static char	**redir_addtomat(const char **tab, char **str, t_mshell *mshell)
{
	int		len;
	char	**new_tab;

	len = 0;
	while (ft_strchr("<>", (*str)[len]) && (*str)[len])
		len ++;
	if (ft_strncmp((*str), ">", len) && ft_strncmp((*str), ">>", len)
		&& ft_strncmp((*str), "<", len) && ft_strncmp((*str), "<<", len))
		return (printf("mshell: parse error near '%c'\n", *(*str)), NULL);
	new_tab = expand_matrix(tab, arg_quotes((*str), len, mshell));
	if (!new_tab)
		return (perror("cmd_split: "), NULL);
	while (ft_strchr(WHTSPACES, (*str)[len]) && (*str)[len])
		(*str)++;
	(*str) += len;
	len = 0;
	new_tab = arg_addtomat((MATRIX)new_tab, str, mshell);
	return (new_tab);
}

static int	init_tokenize(char const *prompt, t_cmdtab **tct, char ***cl)
{
	*tct = ft_calloc(1, sizeof(t_cmdtab));
	if (!*tct)
		return (perror("mshell"), 1);
	*cl = cmd_split(prompt);
	if (!*cl)
		return (1);
	(*tct)->cmdc = get_matrixlen((MATRIX) * cl);
	(*tct)->cmdv = ft_calloc((*tct)->cmdc, sizeof(t_cmd));
	if (!(*tct)->cmdv)
		return (perror("mshell"), 1);
	return (0);
}

static int	parsing_split(char const *s, t_mshell *mshell, t_cmd *cmd)
{
	char	*str;

	str = (char *)s;
	cmd->argv = ft_calloc(1, sizeof(*(cmd->argv)));
	cmd->redirs = ft_calloc(1, sizeof(*(cmd->redirs)));
	if (!cmd->argv || !cmd->redirs)
		return (perror("cmd_split: "), -1);
	while (*str)
	{
		if (*str == '<' || *str == '>')
			cmd->redirs = redir_addtomat((MATRIX)cmd->redirs, &str, mshell);
		else
			cmd->argv = arg_addtomat((MATRIX)cmd->argv, &str, mshell);
		if (!cmd->argv || !cmd->redirs)
			return (-1);
	}
	cmd->argc = get_matrixlen((MATRIX)cmd->argv);
	cmd->redirc = get_matrixlen((MATRIX)cmd->redirs);
	if (cmd->argc == 0 && cmd->redirc == 0)
		return (ft_perror(1, "parse error near '|'"), -1);
	return (0);
}

t_cmdtab	*tokenize(char const *prompt, t_mshell *mshell)
{
	t_cmdtab	*cmdtab;
	char		**cmdlines;
	int			i;

	if (init_tokenize(prompt, &cmdtab, &cmdlines))
	{
		if (cmdlines)
			free_matrix(cmdlines);
		free_cmdtab(cmdtab);
		return (NULL);
	}
	i = -1;
	while (cmdlines[++i])
	{
		if (parsing_split(cmdlines[i], mshell, cmdtab->cmdv + i))
		{
			free_cmdtab(cmdtab);
			cmdtab = NULL;
			break ;
		}
	}
	free_matrix(cmdlines);
	return (cmdtab);
}
