/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:36:11 by jpilotte          #+#    #+#             */
/*   Updated: 2023/05/31 15:29:25 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_input_redirection(const char **cmdv, int *cmdc, const char **input_file) {
    for (int i = 1; i < *cmdc; i++) {
        if (strcmp(cmdv[i], "<") == 0) {
            if (i + 1 >= *cmdc) {
                fprintf(stderr, "Error: no input file specified\n");
                return;
            }
            *input_file = cmdv[i + 1];
            memmove(&cmdv[i], &cmdv[i + 2], (*cmdc - i - 1) * sizeof(char *));
            *cmdc -= 2;
            i--;
        }
    }
}

void handle_output_redirection(const char **cmdv, int *cmdc, const char **output_file, const char **append_file) {
    for (int i = 1; i < *cmdc; i++) {
        if (strcmp(cmdv[i], ">") == 0) {
            if (i + 1 >= *cmdc) {
                fprintf(stderr, "Error: no output file specified\n");
                return;
            }
            *output_file = cmdv[i + 1];
            memmove(&cmdv[i], &cmdv[i + 2], (*cmdc - i - 1) * sizeof(char *));
            *cmdc -= 2;
            i--;
        } else if (strcmp(cmdv[i], ">>") == 0) {
            if (i + 1 >= *cmdc) {
                fprintf(stderr, "Error: no output file specified\n");
                return;
            }
            *append_file = cmdv[i + 1];
            memmove(&cmdv[i], &cmdv[i + 2], (*cmdc - i - 1) * sizeof(char *));
            *cmdc -= 2;
            i--;
        }
    }
}

void handle_heredoc_redirection(const char **cmdv, int *cmdc, const char **delimiter) {
    for (int i = 1; i < *cmdc; i++) {
        if (strcmp(cmdv[i], "<<") == 0) {
            if (i + 1 >= *cmdc) {
                fprintf(stderr, "Error: no delimiter specified\n");
                return;
            }
            *delimiter = cmdv[i + 1];
            memmove(&cmdv[i], &cmdv[i + 2], (*cmdc - i - 1) * sizeof(char *));
            *cmdc -= 2;
            i--;
            char *line = NULL;
            size_t len = 0;
            ssize_t nread;
            while ((nread = getline(&line, &len, stdin)) != -1) {
                if (strcmp(line, *delimiter) == 0) {
                    break;
                }
                write(STDOUT_FILENO, line, nread);
            }
            free(line);
        }
    }
}

int redirections(int cmdc, const char **cmdv) {

    int input_fd = STDIN_FILENO;
    int output_fd = STDOUT_FILENO;
    const char *input_file = NULL;
    const char *output_file = NULL;
    const char *append_file = NULL;
    const char *delimiter = NULL;

    handle_input_redirection(cmdv, &cmdc, &input_file);
    handle_output_redirection(cmdv, &cmdc, &output_file, &append_file);
    handle_heredoc_redirection(cmdv, &cmdc, &delimiter);

    if (input_file != NULL) {
        input_fd = open(input_file, O_RDONLY);
        if (input_fd == -1) {
            perror("open");
            return 1;
        }
    }

    if (output_file != NULL) {
        output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (output_fd == -1) {
            perror("open");
            return 1;
        }
    } else if (append_file != NULL) {
        output_fd = open(append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (output_fd == -1) {
            perror("open");
            return 1;
        }
    }

    if (dup2(input_fd, STDIN_FILENO) == -1) {
        perror("dup2");
        return 1;
    }
    if (dup2(output_fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        return 1;
    }

    system(cmdv[1]);

    if (input_file != NULL) {
        close(input_fd);
    }
    if (output_file != NULL || append_file != NULL) {
        close(output_fd);
    }
    return (-1);
}
