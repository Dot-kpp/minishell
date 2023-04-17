/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:26:30 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/17 12:33:49 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ms_builtins.h"

static int	try_replace_envp(char **split, t_list *envl)
{
	t_ms_env	*content;

	while (envl)
	{
		content = envl->content;
		if (!ft_strncmp(split[0], content->name, ft_strlen(content->name) + 1))
		{
			free(content->value);
			content->value = split[1];
			free(split[0]);
			free(split);
			return (1);
		}
		envl = envl->next;
	}
	return (0);
}

//add new env_var by string sep by '='
//debug split
void	ft_export(char const *var, t_list **envl_ptr)
{
	t_ms_env	*content;
	char		**split;

	if (!envl_ptr)
		return ;
	split = ft_split(var, '='); // error if '=' in value, must split only once
	// if split_count = 1, return bad argument
	if (try_replace_envp(split, *envl_ptr))
		return ;
	content = malloc(sizeof(t_ms_env));
	content->name = split[0];
	content->value = split[1];
	ft_lstadd_back(envl_ptr, ft_lstnew((void *)content));
	free(split);
	return ;
}
