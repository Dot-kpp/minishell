/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:26:30 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/18 11:47:41 by fgeslin          ###   ########.fr       */
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
//check export with no args
void	ft_export(int argc, char const *argv[], t_list **envl)
{
	t_ms_env	*content;
	char		**split;

	if (!envl || argc > 2)
		return ;
	split = ft_split(argv[1], '='); // error if '=' in value, must split only once
	// if split_count = 1, return bad argument
	if (try_replace_envp(split, *envl))
		return ;
	content = malloc(sizeof(t_ms_env));
	content->name = split[0];
	content->value = split[1];
	ft_lstadd_back(envl, ft_lstnew((void *)content));
	free(split);
	return ;
}
