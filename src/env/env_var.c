/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:39:49 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/18 12:32:28 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ms_builtins.h"

// t_list	*get_envl(t_list *new_envl)
// {
// 	static t_list	*envl = NULL;

// 	if (new_envl && !envl)
// 		envl = new_envl;
// 	return (envl);
// }

//free envl->content, name & value
void	free_env_content(void *arg)
{
	t_ms_env	*content;

	content = (t_ms_env *)arg;
	free(content->name);
	free(content->value);
	free(content);
}

//clear envl
void	free_env(t_list *envl)
{
	ft_lstclear(&envl, &free_env_content);
}

//init envl
//gibblish
void	init_env(char const *env[], t_list **envl)
{
	int			i;

	i = -1;
	while (env[++i])
		ft_export(2, env - 1 + i, envl);
}

//get env value by name
char	*get_envp(t_list *envl, char const *name)
{
	t_ms_env	*content;

	while (envl)
	{
		content = envl->content;
		if (!ft_strncmp(content->name, name, ft_strlen(content->name)))
			return (content->value);
		envl = envl->next;
	}
	return (NULL);
}