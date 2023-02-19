#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_ARGS 64
#define MAX_ARG_LEN 256

int main(int argc, char **argv) {
    char *input;
    char *args[MAX_ARGS];
    int num_args;
    int i;
    int status;
    pid_t pid;
    char *path;

    while (1) {
        input = readline("shell> ");
        if (!input) {
            break;
        }
        if (strlen(input) == 0) {
            continue;
        }
        add_history(input);

        num_args = 0;
        args[num_args] = strtok(input, " ");
        while (args[num_args] != NULL) {
            num_args++;
            if (num_args == MAX_ARGS) {
                fprintf(stderr, "too many arguments\n");
                break;
            }
            args[num_args] = strtok(NULL, " ");
        }

        if (num_args == 0) {
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        if (strcmp(args[0], "cd") == 0) {
            if (num_args < 2) {
                fprintf(stderr, "cd: missing argument\n");
                continue;
            }
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
            continue;
        }

        if (strcmp(args[0], "history") == 0) {
            HIST_ENTRY **hist_list = history_list();
            if (hist_list) {
                for (i = 0; hist_list[i] != NULL; i++) {
                    printf("%4d  %s\n", i+history_base, hist_list[i]->line);
                }
            }
            continue;
        }

        pid = fork();
        if (pid == 0) {
            for (i = 0; i < num_args; i++) {
                if (strchr(args[i], '$') != NULL) {
                    char *var = strchr(args[i], '$') + 1;
                    char *value = getenv(var);
                    if (value) {
                        strncpy(args[i], value, MAX_ARG_LEN);
                    } else {
                        fprintf(stderr, "undefined variable: %s\n", var);
                        exit(1);
                    }
                }
            }
            path = getenv("PATH");
            if (!path) {
                path = "/bin:/usr/bin";
            }
            char *tok;
            while ((tok = strsep(&path, ":")) != NULL) {
                char command[MAX_ARG_LEN];
                snprintf(command, sizeof(command), "%s/%s", tok, args[0]);
                if (access(command, X_OK) == 0) {
                    execve(command, args, NULL);
                    perror("execve");
                    exit(1);
                }
            }
            fprintf(stderr, "%s: command not found\n", args[0]);
            exit(1);
        } else if (pid < 0) {
            perror("fork");
        } else {
            waitpid(pid, &status, 0);
        }
    }

    free(input);

    return 0;
}
