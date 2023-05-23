#ifndef MINISHELL_H
#define MINISHELL_H

#define READLINE_LIBRARY

# include "../lib/libft/headers/libft.h"
#include "../lib/readline/includes/readline.h"
#include "../lib/readline/includes/history.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <limits.h>


#define MAX_PATH_LENGTH 1024
#define MAX_ARGS 128

typedef struct s_data
{
	char	*line;
	char	**args;
	char	*input;
	char	cwd[PATH_MAX];
	int 	previous_exit_status;
}				t_data;


//Unit tests, remove before pushing project for grading
char **ms_parse_input(char *input);
void ms_free_args(char **args);
int ms_execute(char **args);
int test_main();


//init_data
t_data *get_data(void);
void init_data(void);

//errors and exit functions
void exit_all(void);
void cwd_check(char *cwd);
void free_input(void);

//pipes
void start_piping(t_list **envl, t_data *data);

//signals
void signal_handler(int signo);
void new_prompt_signal(void);

//redirections
int open_output_file(char *filename, int flags, mode_t mode);
void handle_input_redirection(char **argv, int *argc, char **input_file);
void handle_output_redirection(char **argv, int *argc, char **output_file, char **append_file);
void handle_heredoc_redirection(char **argv, int *argc, char **delimiter);

#endif