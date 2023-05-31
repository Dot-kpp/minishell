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

void handle_input_redirection(char **cmdv, int *cmdc, char **input_file) {
    for (int i = 1; i < *cmdc; i++) {
        if (strcmp(cmdv[i], "<") == 0) {
            if (i + 1 >= *cmdc) {
                fprintf(stderr, "Error: no input file specified\n");
                exit(1);
            }
            *input_file = cmdv[i + 1];
            memmove(&cmdv[i], &cmdv[i + 2], (*cmdc - i - 1) * sizeof(char *));
            *cmdc -= 2;
            i--;
        }
    }
}

void handle_output_redirection(char **cmdv, int *cmdc, char **output_file, char **append_file) {
    for (int i = 1; i < *cmdc; i++) {
        if (strcmp(cmdv[i], ">") == 0) {
            if (i + 1 >= *cmdc) {
                fprintf(stderr, "Error: no output file specified\n");
                exit(1);
            }
            *output_file = cmdv[i + 1];
            memmove(&cmdv[i], &cmdv[i + 2], (*cmdc - i - 1) * sizeof(char *));
            *cmdc -= 2;
            i--;
        } else if (strcmp(cmdv[i], ">>") == 0) {
            if (i + 1 >= *cmdc) {
                fprintf(stderr, "Error: no output file specified\n");
                exit(1);
            }
            *append_file = cmdv[i + 1];
            memmove(&cmdv[i], &cmdv[i + 2], (*cmdc - i - 1) * sizeof(char *));
            *cmdc -= 2;
            i--;
        }
    }
}

void handle_heredoc_redirection(char **cmdv, int *cmdc, char **delimiter) {
    for (int i = 1; i < *cmdc; i++) {
        if (strcmp(cmdv[i], "<<") == 0) {
            if (i + 1 >= *cmdc) {
                fprintf(stderr, "Error: no delimiter specified\n");
                exit(1);
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

int redirections(char **cmdv, int cmdc) {
    if (cmdc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", cmdv[0]);
        return 1;
    }

    int input_fd = STDIN_FILENO;
    int output_fd = STDOUT_FILENO;
    char *input_file = NULL;
    char *output_file = NULL;
    char *append_file = NULL;
    char *delimiter = NULL;

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



// #include <fcntl.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>


// int open_output_file(char *filename, int flags, mode_t mode) {
//     int fd = open(filename, flags, mode);
//     if (fd == -1) {
//         perror("open");
//     }
//     return fd;
// }

// void handle_input_redirection(char **cmd_tab->cmdv, int *cmd_tab->cmdc, char **input_file) {
//     for (int i = 1; i < *cmd_tab->cmdc; i++) {
//         if (strcmp(cmd_tab->cmdv[i], "<") == 0) {
//             if (i + 1 >= *cmd_tab->cmdc) {
//                 fprintf(stderr, "Error: no input file specified\n");
//                 exit(1);
//             }
//             *input_file = cmd_tab->cmdv[i + 1];
//             memmove(&cmd_tab->cmdv[i], &cmd_tab->cmdv[i + 2], (*cmd_tab->cmdc - i - 1) * sizeof(char *));
//             *cmd_tab->cmdc -= 2;
//             i--;
//         }
//     }
// }

// void handle_output_redirection(char **cmd_tab->cmdv, int *cmd_tab->cmdc, char **output_file, char **append_file) {
//     for (int i = 1; i < *cmd_tab->cmdc; i++) {
//         if (strcmp(cmd_tab->cmdv[i], ">") == 0) {
//             if (i + 1 >= *cmd_tab->cmdc) {
//                 fprintf(stderr, "Error: no output file specified\n");
//                 exit(1);
//             }
//             *output_file = cmd_tab->cmdv[i + 1];
//             memmove(&cmd_tab->cmdv[i], &cmd_tab->cmdv[i + 2], (*cmd_tab->cmdc - i - 1) * sizeof(char *));
//             *cmd_tab->cmdc -= 2;
//             i--;
//         } else if (strcmp(cmd_tab->cmdv[i], ">>") == 0) {
//             if (i + 1 >= *cmd_tab->cmdc) {
//                 fprintf(stderr, "Error: no output file specified\n");
//                 exit(1);
//             }
//             *append_file = cmd_tab->cmdv[i + 1];
//             memmove(&cmd_tab->cmdv[i], &cmd_tab->cmdv[i + 2], (*cmd_tab->cmdc - i - 1) * sizeof(char *));
//             *cmd_tab->cmdc -= 2;
//             i--;
//         }
//     }
// }

// void handle_heredoc_redirection(char **cmd_tab->cmdv, int *cmd_tab->cmdc, char **delimiter) {
//     for (int i = 1; i < *cmd_tab->cmdc; i++) {
//         if (strcmp(cmd_tab->cmdv[i], "<<") == 0) {
//             if (i + 1 >= *cmd_tab->cmdc) {
//                 fprintf(stderr, "Error: no delimiter specified\n");
//                 exit(1);
//             }
//             *delimiter = cmd_tab->cmdv[i + 1];
//             memmove(&cmd_tab->cmdv[i], &cmd_tab->cmdv[i + 2], (*cmd_tab->cmdc - i - 1) * sizeof(char *));
//             *cmd_tab->cmdc -= 2;
//             i--;
//             char *line = NULL;
//             size_t len = 0;
//             ssize_t nread;
//             while ((nread = getline(&line, &len, stdin)) != -1) {
//                 if (strcmp(line, *delimiter) == 0) {
//                     break;
//                 }
//                 write(STDOUT_FILENO, line, nread);
//             }
//             free(line);
//         }
//     }
// }

// int redirections(t_cmdtab	*cmd_tab)
// {
//         if (cmd_tab->cmdc < 2) {
//         fprintf(stderr, "Usage: %s <command>\n", cmd_tab->cmdv[0]);
//         return 1;
//     }

//     int input_fd = STDIN_FILENO;
//     int output_fd = STDOUT_FILENO;
//     char *input_file = NULL;
//     char *output_file = NULL;
//     char *append_file = NULL;
//     char *delimiter = NULL;

//     handle_input_redirection(cmd_tab->cmdv, &cmd_tab->cmdc, &input_file);
//     handle_output_redirection(cmd_tab->cmdv, &cmd_tab->cmdc, &output_file, &append_file);
//     handle_heredoc_redirection(cmd_tab->cmdv, &cmd_tab->cmdc, &delimiter);

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

//     system(cmd_tab->cmdv[1]);

//     if (input_file != NULL) {
//         close(input_fd);
//     }
//     if (output_file != NULL || append_file != NULL) {
//         close(output_fd);
//     }
//     return 0;
// }

// int main(int cmd_tab->cmdc, char *cmd_tab->cmdv[]) {
//     if (cmd_tab->cmdc < 2) {
//         fprintf(stderr, "Usage: %s <command>\n", cmd_tab->cmdv[0]);
//         return 1;
//     }

//     int input_fd = STDIN_FILENO;
//     int output_fd = STDOUT_FILENO;
//     char *input_file = NULL;
//     char *output_file = NULL;
//     char *append_file = NULL;
//     char *delimiter = NULL;

//     handle_input_redirection(cmd_tab->cmdv, &cmd_tab->cmdc, &input_file);
//     handle_output_redirection(cmd_tab->cmdv, &cmd_tab->cmdc, &output_file, &append_file);
//     handle_heredoc_redirection(cmd_tab->cmdv, &cmd_tab->cmdc, &delimiter);

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

//     system(cmd_tab->cmdv[1]);

//     if (input_file != NULL) {
//         close(input_fd);
//     }
//     if (output_file != NULL || append_file != NULL) {
//         close(output_fd);
//     }

//     return 0;
//     }
