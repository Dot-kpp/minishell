/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:21:23 by fgeslin           #+#    #+#             */
/*   Updated: 2023/05/24 12:21:46 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ms_builtins.h"

void	free_cmdtab(t_cmdtab *cmd_tab)
{
	int	cmd_i;
	int	arg_i;

	cmd_i = -1;
	while (++cmd_i < cmd_tab->cmdc)
	{
		arg_i = -1;
		while (++arg_i < cmd_tab->cmdv[cmd_i].argc)
			free(cmd_tab->cmdv[cmd_i].argv[arg_i]);
		free(cmd_tab->cmdv[cmd_i].argv);
		free_matrix(cmd_tab->cmdv[cmd_i].redirs);
	}
	free(cmd_tab->cmdv);
	free(cmd_tab);
}

char	**freetab(char **tab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		*(tab[i]) = 0;
		free(tab[i]);
	}
	*tab = 0;
	free(tab);
	return (0);
}
