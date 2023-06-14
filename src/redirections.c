/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:36:11 by jpilotte          #+#    #+#             */
/*   Updated: 2023/06/14 14:08:12 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void	handle_heredoc_redirection(char **argv, int *argc,
		char **delimiter, char **input_file)
{
	int		i;
	int		tmpfd;
	char	*line;
	char	*error_message;

	i = 0;
	error_message = "Error: no delimiter specified\n";
	while (i < *argc)
	{
		if (ft_strcmp(argv[i], "<<") == 0)
		{
	        tmpfd = open(TMPFILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (i + 1 >= *argc)
			{
				write(STDERR_FILENO, error_message, ft_strlen(error_message));
				exit(1);
			}
			write(STDOUT_FILENO, "heredoc>", 9);
			*delimiter = argv[i + 1];
			ft_memmove(&argv[i], &argv[i + 2],
				(*argc - i - 1) * sizeof(char *));
			*argc -= 2;
			i--;
			// line = get_next_line(STDIN_FILENO);
			while ((line = get_next_line(STDIN_FILENO)))
			{
				if (ft_strncmp(line, *delimiter, ft_strlen(*delimiter)) != 0)
					write(STDOUT_FILENO, "heredoc>", 9);
				else if (ft_strncmp(line, *delimiter,
						ft_strlen(*delimiter)) == 0)
				{
					free(line);
					break ;
				}
				write(tmpfd, line, ft_strlen(line));
				free(line);
			}
            *input_file = TMPFILE;
            close(tmpfd);
		}
		i++;
	}
}

int	call_redirections(t_cmd *cmd)
{
	int		input_fd;
	int		output_fd;
	char	*input_file;
	char	*output_file;
	char	*append_file;
	char	*delimiter;

	input_fd = STDIN_FILENO;
	output_fd = STDOUT_FILENO;
	input_file = NULL;
	output_file = NULL;
	append_file = NULL;
	delimiter = NULL;
	handle_input_redirection(cmd->redirs,
		&cmd->redirc, &input_file);
	handle_output_redirection(cmd->redirs,
		&cmd->redirc, &output_file, &append_file);
	handle_heredoc_redirection(cmd->redirs,
		&cmd->redirc, &delimiter, &input_file);
	if (input_file != NULL)
	{
		input_fd = open(input_file, O_RDONLY);
		if (input_fd == -1)
			return (perror("open"), -1);
	}
	if (append_file != NULL)
	{
		output_fd = open_output_file(append_file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (output_fd == -1)
            return (perror("open"), -1);
	}
	if (output_file != NULL)
	{
		output_fd = open_output_file(output_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_fd == -1)
	    	return (perror("open"), -1);
	}
	if (dup2(input_fd, STDIN_FILENO) == -1)
		return (perror("dup2"), -1);
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		return (perror("dup2"), -1);
	if (input_file != NULL)
		close(input_fd);
	if (output_file != NULL || append_file != NULL)
		close(output_fd);
	return (-1);
}
