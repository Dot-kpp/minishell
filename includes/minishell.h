/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:17:57 by fgeslin           #+#    #+#             */
/*   Updated: 2023/05/16 11:17:57 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY
# include "../lib/libft/headers/libft.h"
# include "../lib/readline/includes/readline.h"
# include "../lib/readline/includes/history.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>

# define MAX_PATH_LENGTH 1024
# define MAX_ARGS 128

# define WHTSPACES "\t\n\v\f\r \0"

typedef struct s_cmd
{
	int		argc;
	char	**argv;

	char	*red_in;
	char	*red_out;
	char	*red_app;
	char	*red_her;
}	t_cmd;

typedef struct s_cmdtab
{
	int		cmdc;
	t_cmd	*cmdv;
}	t_cmdtab;


typedef struct s_data
{
	char	*line;
	char	**args;
	char	*input;
	char	cwd[PATH_MAX];
}				t_data;

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

//parsing
char	*ft_append(char *s1, char const *s2, int n);

#endif