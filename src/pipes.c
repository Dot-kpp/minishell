/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:08:45 by jpilotte          #+#    #+#             */
/*   Updated: 2023/05/09 13:12:24 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ms_builtins.h"

int count_args(char **args) {
    int count = 0;
    while (*args != NULL) {
        count++;
        args++;
    }
    return count;
}

int exec_pipeline(t_cmdtab *cmd_tab, t_mshell *mshell) {
    (void) mshell;
    int num_cmds = cmd_tab->cmdc;
    int exit_status = 0;
    int pipefd[2];
    pid_t pid;
    int i = 0;
    int prev_pipefd[2] = {-1, -1};

    while (i < num_cmds) {
        if (i < num_cmds - 1) {
            if (pipe(pipefd) == -1) {
                perror("pipe");
                exit(exit_status);
            }
        }
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(exit_status);
        } else if (pid == 0) {
            // Child process
            if (i > 0) {
                // Redirect input from previous command
                dup2(prev_pipefd[0], STDIN_FILENO);
                close(prev_pipefd[0]);
                close(prev_pipefd[1]);
            }
            if (i < num_cmds - 1) {
                // Redirect output to next command
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
            }
            // Execute command
            execvp(cmd_tab->cmdv[i].argv[0], cmd_tab->cmdv[i].argv);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            if (prev_pipefd[0] != -1) {
                close(prev_pipefd[0]);
                close(prev_pipefd[1]);
            }
            if (i < num_cmds - 1) {
                prev_pipefd[0] = pipefd[0];
                prev_pipefd[1] = pipefd[1];
            }
            waitpid(pid, &exit_status, 0);
        }
        i++;
    }

    return exit_status;
}

// int exec_pipeline(int *argc, char **argv, t_mshell *mshell) {
//     int num_cmds = *argc;
//     int exit_status = 0;
//     int pipefd[2];
//     pid_t pid;
//     int i = 0;

//     while (i < num_cmds) {
//         if (i < num_cmds - 1) {
//             if (pipe(pipefd) == -1) {
//                 perror("pipe");
//                 exit(exit_status);
//             }
//         }
//         pid = fork();
//         if (pid == -1) {
//             perror("fork");
//             exit(exit_status);
//         }
//         if (pid == 0) {
//             if (i > 0) {
//                 if (dup2(pipefd[0], STDIN_FILENO) == -1) {
//                     perror("dup2");
//                     exit(exit_status);
//                 }
//                 close(pipefd[0]);
//             }
//             if (i < num_cmds - 1) {
//                 if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
//                     perror("dup2");
//                     exit(exit_status);
//                 }
//                 close(pipefd[1]);
//             }
//             char **cmd_argv = argv + i;
//             int cmd_argc = count_args(*&cmd_argv);
//             t_cmd cmd = { .argc = cmd_argc, .argv = cmd_argv };
//             // exit_status = exec_cmd(cmd, mshell);
//             exit_status = execve(cmd.argv[0], cmd.argv, mshell->env);
//             exit(exit_status);
//         } else {
//             if (i > 0) {
//                 close(pipefd[0]);
//             }
//             if (i < num_cmds - 1) {
//                 close(pipefd[1]);
//             }
//             waitpid(pid, &exit_status, 0);
//         }
//         i++;
//     }
//     return exit_status;
// }