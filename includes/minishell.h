#ifndef MINISHELL_H
#define MINISHELL_H


# include "../lib/libft/headers/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


typedef struct s_data
{
	char	*line;
	char	**args;
}				t_data;


#endif