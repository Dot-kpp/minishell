/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_rpl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:06:01 by fgeslin           #+#    #+#             */
/*   Updated: 2023/05/08 10:53:10 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TEMP FUNC (to clean / find a better way)
char	*ft_strnrpl(char const *str, char const *pst, char const *cpy, int n)
{
	char	*stitched;
	char	*cursor;
	size_t	len;
	int		i;

	len = strlen(str) - strlen(pst) + strlen(cpy) + 1;
	if (n > 0)
		cursor = ft_strnstr(str, pst, n);
	else
		cursor = ft_strnstr(str, pst, strlen(str));
	if (!cursor)
		return (ft_strdup(str));
	i = 0;
	while (str + i != cursor)
		i++;
	stitched = malloc(len);
	if (!stitched)
		return (0);
	ft_strlcpy(stitched, str, i + 1);
	ft_strlcat(stitched, cpy, len);
	ft_strlcat(stitched, str + i + strlen(pst), len);
	return (stitched);
}

char	**env_rpl(char **argv, t_list **envl)
{

}
