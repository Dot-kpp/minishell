/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:26:30 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/21 15:08:27 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ms_builtins.h"

static char	**ft_splitonce(char const *s, char c)
{
	char	**split;
	int		i;

	i = -1;
	while (s[++i] != c)
		if (!s[i])
			return (NULL);
	split = malloc(2 * sizeof(*split));
	split[0] = ft_calloc(i + 2, sizeof(char));
	ft_strlcpy(split[0], s, i + 1);
	split[1] = ft_strdup(s + i + 1);
	return (split);
}

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
//check name alphanum
int	ft_export(int argc, char const *argv[], t_list **envl)
{
	t_ms_env	*content;
	char		**split;

	if (!envl)
		return (printf("ft_export: env_list error\n"), 1);
	if (argc != 2)
		return (printf("ft_export: bad arguments\n"), 1);
	split = ft_splitonce(argv[1], '=');
	if (!split)
		return (printf("ft_export: bad arguments\n"), 1);
	if (try_replace_envp(split, *envl))
		return (0);
	content = malloc(sizeof(t_ms_env));
	content->name = split[0];
	content->value = split[1];
	ft_lstadd_back(envl, ft_lstnew((void *)content));
	free(split);
	return (0);
}
