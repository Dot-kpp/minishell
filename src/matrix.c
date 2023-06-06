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

static int	get_matrixlen(const char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

char	**expand_matrix(const char **matrix, const char *new_line)
{
	int		size;
	char	**new_matrix;

	size = get_matrixlen(matrix);
	new_matrix = ft_calloc(size + 2, sizeof(*new_matrix));
	new_matrix[size] = ft_strdup(new_line);
	while (--size >= 0)
		new_matrix[size] = (char *)matrix[size];
	return (free(matrix), new_matrix);
}

char	**shrink_matrix(const char **matrix, const char *to_remove)
{
	int		i;
	int		del;
	int		size;
	char	**new_matrix;

	size = get_matrixlen(matrix);
	new_matrix = ft_calloc(size + 1, sizeof(*new_matrix));
	i = 0;
	del = 0;
	while (matrix[i + del])
	{
		if (!ft_strncmp(matrix[i + del], to_remove, ft_strlen(to_remove)))
		{
			free((void *)matrix[i + del]);
			del++;
		}
		else
		{
			new_matrix[i] = (char *)matrix[i + del];
			i++;
		}
	}
	return (free(matrix), new_matrix);
}

char	**dup_matrix(const char **matrix)
{
	char	**new_matrix;
	int		size;
	int		i;

	size = get_matrixlen(matrix);
	new_matrix = ft_calloc(size + 1, sizeof(*new_matrix));
	i = -1;
	while (++i < size)
		new_matrix[i] = ft_strdup(matrix[i]);
	return (new_matrix);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
	{
		*(matrix[i]) = 0;
		free(matrix[i]);
	}
	*matrix = 0;
	free(matrix);
}
