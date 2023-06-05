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

#include "../includes/minishell.h"
#include "../includes/ms_builtins.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int open_output_file(char *filename, int flags, mode_t mode) {
    int fd = open(filename, flags, mode);
    if (fd == -1) {
        perror("open");
    }
    return fd;
}

void handle_input_redirection(char **argv, int *argc, char **input_file) {
    for (int i = 0; i < *argc; i++) {
        if (strcmp(argv[i], "<") == 0) {
            if (i + 1 >= *argc) {
                fprintf(stderr, "Error: no input file specified\n");
                exit(1);
            }
            *input_file = argv[i + 1];
            memmove(&argv[i], &argv[i + 2], (*argc - i - 1) * sizeof(char *));
            *argc -= 2;
            i--;
        }
    }
}

void handle_output_redirection(char **argv, int *argc, char **output_file, char **append_file) {
    for (int i = 0; i < *argc; i++) {
        if (strcmp(argv[i], ">") == 0) {
            if (i + 1 >= *argc) {
                fprintf(stderr, "Error: no output file specified\n");
                exit(1);
            }
            *output_file = argv[i + 1];
            memmove(&argv[i], &argv[i + 2], (*argc - i - 1) * sizeof(char *));
            *argc -= 2;
            i--;
        } else if (strcmp(argv[i], ">>") == 0) {
            if (i + 1 >= *argc) {
                fprintf(stderr, "Error: no output file specified\n");
                exit(1);
            }
            *append_file = argv[i + 1];
            memmove(&argv[i], &argv[i + 2], (*argc - i - 1) * sizeof(char *));
            *argc -= 2;
            i--;
        }
    }
}

void handle_heredoc_redirection(char **argv, int *argc, char **delimiter) {
    for (int i = 0; i < *argc; i++) {
        if (strcmp(argv[i], "<<") == 0) {
            if (i + 1 >= *argc) {
                fprintf(stderr, "Error: no delimiter specified\n");
                exit(1);
            }
            *delimiter = argv[i + 1];
            memmove(&argv[i], &argv[i + 2], (*argc - i - 1) * sizeof(char *));
            *argc -= 2;
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

int call_redirections(t_cmd *cmd, t_mshell *mshell)
{
    (void)mshell;
    int input_fd = STDIN_FILENO;
    int output_fd = STDOUT_FILENO;
    char *input_file = NULL;
    char *output_file = NULL;
    char *append_file = NULL;
    char *delimiter = NULL;

    handle_input_redirection(cmd->redirs, &cmd->redirc, &input_file);
    handle_output_redirection(cmd->redirs, &cmd->redirc, &output_file, &append_file);
    handle_heredoc_redirection(cmd->redirs, &cmd->redirc, &delimiter);

    if (input_file != NULL) {
        input_fd = open(input_file, O_RDONLY);
        if (input_fd == -1) {
            perror("open");
            return -1;
        }
    }

    if (output_file != NULL) {
        output_fd = open_output_file(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (output_fd == -1) {
            perror("open");
            return -1;
        }
    } else if (append_file != NULL) {
        output_fd = open_output_file(append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (output_fd == -1) {
            perror("open");
            return -1;
        }
    }

    if (dup2(input_fd, STDIN_FILENO) == -1) {
        perror("dup2");
        return -1;
    }
    if (dup2(output_fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        return -1;
    }

    // exit_status = call_builtin(cmd.argc, (const char **)cmd.argv, mshell);
    // if (exit_status > -1) {
    //     return exit_status;
    // }
    // exit_status = execve(expand_cmd(cmd.argv[0], ms_getenv("PATH", (const char **)mshell->env)), cmd.argv, mshell->env);

    if (input_file != NULL) {
        close(input_fd);
    }
    if (output_file != NULL || append_file != NULL) {
        close(output_fd);
    }
    return -1;
}

// int main(int argc, char *argv[]) {
//     if (argc < 2) {
//         fprintf(stderr, "Usage: %s <command>\n", argv[0]);
//         return 1;
//     }

//     int input_fd = STDIN_FILENO;
//     int output_fd = STDOUT_FILENO;
//     char *input_file = NULL;
//     char *output_file = NULL;
//     char *append_file = NULL;
//     char *delimiter = NULL;

//     handle_input_redirection(argv, &argc, &input_file);
//     handle_output_redirection(argv, &argc, &output_file, &append_file);
//     handle_heredoc_redirection(argv, &argc, &delimiter);

//     if (input_file != NULL) {
//         input_fd = open(input_file, O_RDONLY);
//         if (input_fd == -1) {
//             perror("open");
//             return 1;
//         }
//     }

//     if (output_file != NULL) {
//         output_fd = open_output_file(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//         if (output_fd == -1) {
//             perror("open");
//             return 1;
//         }
//     } else if (append_file != NULL) {
//         output_fd = open_output_file(append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
//         if (output_fd == -1) {
//             perror("open");
//             return 1;
//         }
//     }

//     if (dup2(input_fd, STDIN_FILENO) == -1) {
//         perror("dup2");
//         return 1;
//     }
//     if (dup2(output_fd, STDOUT_FILENO) == -1) {
//         perror("dup2");
//         return 1;
//     }

//     system(argv[1]);

//     if (input_file != NULL) {
//         close(input_fd);
//     }
//     if (output_file != NULL || append_file != NULL) {
//         close(output_fd);
//     }

//     return 0;
//     }