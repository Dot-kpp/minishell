/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:24:34 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/19 12:37:45 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ms_builtins.h"

//print envl
int	ft_env(int argc, char const *argv[], t_list **envl_ptr)
{
	t_list		*envl;
	t_ms_env	*content;

	(void)argc;
	(void)argv;
	envl = *envl_ptr;
	while (envl != NULL)
	{
		content = envl->content;
		printf("%s=%s\n", content->name, content->value);
		envl = envl->next;
	}
	return (0);
}
