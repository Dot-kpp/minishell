/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:07:33 by fgeslin           #+#    #+#             */
/*   Updated: 2023/05/23 14:07:46 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**expand_matrix(char **matrix, char *new_line)
{
	int		size;
	char	**new_matrix;

	size = 0;
	while (matrix[size])
		size++;
	new_matrix = ft_calloc(size + 2, sizeof(*new_matrix));
	new_matrix[size] = ft_strdup(new_line);
	while (--size >= 0)
		new_matrix[size] = matrix[size];
	free(matrix);
	return (new_matrix);
}
