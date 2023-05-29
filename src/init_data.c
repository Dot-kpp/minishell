/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:13:34 by jpilotte          #+#    #+#             */
/*   Updated: 2023/05/08 12:13:34 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//init singleton for "global" use *replaces global variables
t_cmdtab *get_cmdtab(void)
{
	static t_cmdtab *cmdtab = NULL;

	if(cmdtab == NULL)
		cmdtab = (t_cmdtab *)malloc(sizeof(t_cmdtab));
	return (cmdtab);
}

void init_cmdtab(void)
{
	t_cmdtab *cmdtab;

	cmdtab = get_cmdtab();
}
