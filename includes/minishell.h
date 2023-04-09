#ifndef MINISHELL_H
#define MINISHELL_H


# include "../lib/libft/headers/libft.h"
// # include "../lib/readline/readline.h"
// # include "../lib/readline/history.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_data
{
	char	*line;
	char	**args;
}				t_data;


#endif

//init_data
t_data *get_data(void);
void init_data(void);

//errors and exit functions
void exit_all(void);