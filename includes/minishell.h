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

	char	*rin;
	char	*rout;
	char	*rapp;
	char	*rher;
}	t_cmd;

typedef struct s_cmdtab
{
	int		cmdc;
	t_cmd	*cmdv;
	int		exit_status;
}	t_cmdtab;


//Unit tests, remove before pushing project for grading
char **ms_parse_input(char *input);
void ms_free_args(char **args);
int ms_execute(char **args);
int test_main();


//init_data
t_cmdtab	*get_cmdtab(void);
void		init_cmdtab(void);

//errors and exit functions
void		exit_all(void);
void		cwd_check(char *cwd);
// void		free_input(void);

//pipes
// void		start_piping(t_list **envl, t_data *data);

//signals
void		signal_handler(int signo);
void		new_prompt_signal(void);

//parsing
t_cmdtab	*tokenize(char const *prompt, t_list **envl);
//parsing utils
char		*ft_append(char *s1, char const *s2, int n);
int			nextquote(char const *s);
int			smartcount(char const *s, char const *sep, int trim_sep);

//freeing
void		free_cmdtab(t_cmdtab *cmd_tab);
char		**freetab(char **tab, int size);

//redirections
int open_output_file(char *filename, int flags, mode_t mode);
void handle_input_redirection(char **argv, int *argc, char **input_file);
void handle_output_redirection(char **argv, int *argc, char **output_file, char **append_file);
void handle_heredoc_redirection(char **argv, int *argc, char **delimiter);

#endif