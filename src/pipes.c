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

int exec_pipeline(int *argc, char **argv, t_mshell *mshell) {
    int num_cmds = *argc;
    int exit_status = 0;
    int pipefd[2];
    pid_t pid;

    for (int i = 0; i < num_cmds; i++) {
        if (i < num_cmds - 1) {
            if (pipe(pipefd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            if (i > 0) {
                if (dup2(pipefd[0], STDIN_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(pipefd[0]);
                close(pipefd[1]);
            }

            if (i < num_cmds - 1) {
                if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(pipefd[0]);
                close(pipefd[1]);
            }

            char **cmd_argv = argv + i;
            int cmd_argc = count_args(*&cmd_argv);
            t_cmd cmd = { .argc = cmd_argc, .argv = cmd_argv };
            exit_status = exec_cmd(cmd, mshell);
            exit(-1);
        } else {
            if (i > 0) {
                close(pipefd[0]);
                close(pipefd[1]);
            }
            waitpid(pid, &exit_status, 0);
        }
    }

    return (-1);
}

// int main(void)
// {
//     t_mshell    mshell;
//     t_cmd       *cmd;
//     t_pipeline  pipeline;

//     mshell.env = NULL; // Set up your environment variables here

//     cmd = parse_pipe_cmd("ls | grep minishell", 0, 0, &mshell);
//     pipeline.cmds[0] = cmd;
//     pipeline.num_cmds = 1;
//     pipeline.pipeline = 1;

//     exec_pipeline(pipeline, &mshell);

//     return (0);
// }

// static int  get_argsize(char **arg)
// {
// 	int i;

// 	i = 0;
// 	while (arg[i])
// 		i++;
// 	return (i);
// }

// void start_piping(t_list **envl, t_data *data)
// {
//     // int		i;
//     // int		fd[2];
//     // int		fd_in;
//     // pid_t	pid;

//     // i = 0;
//     // fd_in = 0;
//     // while (args[i])
//     // {
//     //     pipe(fd);
//     //     pid = fork();
//     //     if (pid == 0)
//     //     {
//     //         dup2(fd_in, 0);
//     //         if (args[i + 1])
//     //             dup2(fd[1], 1);
//     //         close(fd[0]);
//     //         exit(0);
//     //     }
//     //     else
//     //     {
//     //         wait(NULL);
//     //         close(fd[1]);
//     //         fd_in = fd[0];
//     //         i++;
//     //     }
//     // }


//     		// Create child process to execute command
// 		pid_t pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork() error");
// 			return;
// 		}
// 		else if (pid == 0)
// 		{
// 			// Child process
//             char *args[] = {"/bin/sh", "-c", data->input, NULL};
//             data->args = args;
// 			if (execv(data->args[0], data->args) == -1) 
//             {
//                 perror("execv() error");
//                 exit(1);
//             }
//             call_builtin(get_argsize(args), (const char **)args, envl);
// 		}
//         else
//         {
//         // Parent process
//             int status;
//             if (waitpid(pid, &status, 0) == -1) 
//             {
//                 perror("waitpid() error");
//             }
//         }
// }
