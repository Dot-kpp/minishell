#include "../includes/minishell.h"


//start running minishell overlay
static void minishell(void)
{
	t_data *data;
	(void) data;
    char *input;
    char cwd[1024];

    while (1) {
        // Print the shell prompt
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd() error");
            return;
        }
        printf("%s$ ", cwd);

        // Read user input
        input = readline(NULL);

        // If input is NULL, user has pressed Ctrl-D or EOF has been reached
        if (input == NULL) {
            printf("\n");
            break;
        }
        // If input is empty, continue to next loop iteration
        if (ft_strlen(input) == 0) {
            free(input);
            continue;
        }

        // Add input to history
        add_history(input);

        // Create child process to execute command
        pid_t pid = fork();
                // Display history if "history" is entered
        if (pid == -1) {
            perror("fork() error");
            return;
        }
        else if (pid == 0) {
            // Child process
            char *args[] = {"/bin/sh", "-c", input, NULL};
            execve(args[0], args, NULL);
            perror("execv() error");
            exit(1);
        }
        else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
        }

        free(input);
    }

}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;

	init_data();
	minishell();
	exit_all();
    clear_history();
	
	return (0);
}
