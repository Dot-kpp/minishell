/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:24:34 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/17 12:32:16 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ms_builtins.h"

//print envl
void	ft_env(t_list *envl)
{
	t_ms_env	*content;

	while (envl != NULL)
	{
		content = envl->content;
		printf("%s=%s\n", content->name, content->value);
		envl = envl->next;
	}
}
