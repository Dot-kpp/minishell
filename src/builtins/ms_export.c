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

//add new env_var by string sep by '='
int	ms_export(int argc, char const *argv[], t_mshell *mshell)
{
	int		i;

	if (argc == 1)
		return (print_sortedmatrix((const char **)mshell->env), 0);
	if (argc != 2)
		return (ft_perror(1, "ft_export: bad arguments"), 1);
	i = -1;
	while (argv[1][++i] != '=')
		if (!argv[1][i])
			return (ft_perror(1, "ft_export: bad arguments"), 1);
	if (is_valid_envp(argv[1], i))
		return (update_envp(argv[1], mshell));
	else
		return (ft_perror(2, "ft_export: not valid in this context:",
				argv[1]), 1);
}
