/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:36:11 by jpilotte          #+#    #+#             */
/*   Updated: 2023/06/14 15:58:18 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	read_heredoc_input(char **delimiter, int tmpfd)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (ft_strncmp(line, *delimiter, ft_strlen(*delimiter)) != 0)
			write(STDOUT_FILENO, "heredoc>", 9);
		else if (ft_strncmp(line, *delimiter, ft_strlen(*delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(tmpfd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

void	redir_error(void)
{
	write(STDERR_FILENO, "Error: no delimiter specified\n", 30);
	exit (1);
}

void	handle_heredoc_redirection(char **argv, int *argc,
		char **delimiter, char **input_file)
{
	int		i;
	int		tmpfd;

	i = 0;
	while (i < *argc)
	{
		if (ft_strcmp(argv[i], "<<") == 0)
		{
			dup2(1, STDIN_FILENO);
			tmpfd = open(TMPFILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (i + 1 >= *argc)
				redir_error();
			write(STDOUT_FILENO, "heredoc>", 9);
			*delimiter = argv[i + 1];
			// ft_memmove(&argv[i], &argv[i + 2],
			// 	(*argc - i - 1) * sizeof(char *));
			// *argc -= 2;
			// i--;
			read_heredoc_input(delimiter, tmpfd);
			*input_file = TMPFILE;
			close (tmpfd);
		}
		i++;
	}
}

static int	call_redirections2(t_redirections *redirs, t_cmd *cmd)
{
	redirs->input_fd = STDIN_FILENO;
	redirs->output_fd = STDOUT_FILENO;
	redirs->input_file = NULL;
	redirs->output_file = NULL;
	redirs->append_file = NULL;
	redirs->delimiter = NULL;
	handle_input_redirection(cmd->redirs, &cmd->redirc, &redirs->input_file);
	handle_output_redirection(cmd->redirs, &cmd->redirc,
		&redirs->output_file, &redirs->append_file);
	handle_heredoc_redirection(cmd->redirs, &cmd->redirc,
		&redirs->delimiter, &redirs->input_file);
	if (redirs->input_file != NULL)
	{
		redirs->input_fd = open(redirs->input_file, O_RDONLY);
		if (redirs->input_fd == -1)
			return (perror("open"), -1);
	}
	if (redirs->append_file != NULL)
	{
		redirs->output_fd = open_output_file(redirs->append_file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (redirs->output_fd == -1)
			return (perror("open"), -1);
	}
	return (0);
}

int	call_redirections(t_cmd *cmd)
{
	t_redirections	redirs;

	if (call_redirections2(&redirs, cmd) == -1)
		return (1);
	if (redirs.output_file != NULL)
	{
		redirs.output_fd = open_output_file(redirs.output_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (redirs.output_fd == -1)
			return (perror("open"), 1);
	}
	if (dup2(redirs.input_fd, STDIN_FILENO) == -1
		|| dup2(redirs.output_fd, STDOUT_FILENO) == -1)
		return (perror("dup2"), 1);
	if (redirs.input_file != NULL)
		close(redirs.input_fd);
	if (redirs.output_file != NULL || redirs.append_file != NULL)
		close(redirs.output_fd);
	return (0);
}
