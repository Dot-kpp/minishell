/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:39:04 by jpilotte          #+#    #+#             */
/*   Updated: 2023/06/14 15:48:58 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int	open_output_file(char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
		perror("open");
	return (fd);
}

void	handle_input_redirection(char **argv, int *argc, char **input_file)
{
	int	i;

	i = 0;
	while (i < *argc)
	{
		if (ft_strcmp(argv[i], "<") == 0)
		{
			if (i + 1 >= *argc)
				redir_error();
			*input_file = argv[i + 1];
		}
		i++;
	}
}

void	handle_single_output_redirection(char **argv, int *argc,
	char **file, char *operator)
{
	int	i;

	i = 0;
	while (i < *argc)
	{
		if (ft_strcmp(argv[i], operator) == 0)
		{
			if (i + 1 >= *argc)
				redir_error();
			*file = argv[i + 1];
		}
		i++;
	}
}

void	handle_output_redirection(char **argv, int *argc,
	char **output_file, char **append_file)
{
	handle_single_output_redirection(argv, argc, output_file, ">");
	handle_single_output_redirection(argv, argc, append_file, ">>");
}
