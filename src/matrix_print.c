/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:07:33 by fgeslin           #+#    #+#             */
/*   Updated: 2023/06/01 16:47:07 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	envcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i] && (str1[i] || str2[i]) && (str1[i] == str2[i]))
		i++;
	if (str1[i] == '=')
		return (-1);
	if (str2[i] == '=')
		return (1);
	return ((unsigned char) str1[i] - (unsigned char)str2[i]);
}

void	print_sortedmatrix(char const **matrix)
{
	int		i;
	char	*line;
	char	*nextline;

	i = -1;
	line = (char *)*matrix;
	while (matrix[++i])
	{
		if (envcmp(line, matrix[i]) > 0)
			line = (char *)matrix[i];
	}
	while (line)
	{
		printf("%s\n", line);
		i = -1;
		nextline = 0;
		while (matrix[++i])
		{
			if (envcmp(line, matrix[i]) < 0
				&& (!nextline || envcmp(nextline, matrix[i]) > 0))
				nextline = (char *)matrix[i];
		}
		line = nextline;
	}
}

void	print_matrix(const char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		printf("%s\n", matrix[i]);
}
