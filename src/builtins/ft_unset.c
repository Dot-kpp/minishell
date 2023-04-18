/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:26:00 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/18 11:49:32 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ms_builtins.h"

//del env_var by name
//check if del last one and envl empty
void	ft_unset(int argc, char const *argv[], t_list **envl_ptr)
{
	t_list		*envl;
	t_list		*prev_envl;
	t_ms_env	*content;

	if (argc != 1)
	{
		perror("ft_unset: ");
		exit(1);
	}
	envl = *envl_ptr;
	prev_envl = NULL;
	while (envl)
	{
		content = envl->content;
		if (!ft_strncmp(argv[1], content->name, ft_strlen(content->name) + 1))
		{
			if (!prev_envl)
				*envl_ptr = envl->next;
			else
				prev_envl->next = envl->next;
			ft_lstdelone(envl, free);
			return ;
		}
		prev_envl = envl;
		envl = envl->next;
	}
	return ;
}
