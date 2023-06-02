/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:22:13 by fgeslin           #+#    #+#             */
/*   Updated: 2023/05/23 16:31:58 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// s1 will be freed, s2 const
char	*ft_append(char *s1, char const *s2, int n)
{
	char	*str;
	int		len[2];

	if (!s1)
		return (0);
	if (!s2)
		return (s1);
	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	if (n < len[1])
		len[1] = n;
	str = ft_calloc(len[0] + len[1] + 2, sizeof(*str));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, len[0] + 1);
	ft_strlcat(str, s2, len[0] + len[1] + 1);
	free(s1);
	return (str);
}
