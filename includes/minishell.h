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

typedef struct s_cmd t_cmd;

typedef struct s_pipeline {
    int num_cmds;
    t_cmd *cmds;
} t_pipeline;

typedef struct s_cmd
{
	int		argc;
	char	**argv;
	char 	*input_redir;
    char 	*output_redir;
    char	*append_redir;
	char	*heredoc;
	int 	bg;
	char	**redirs;
	t_pipeline *pipeline; 
}	t_cmd;

typedef struct s_cmdtab
{
	int		cmdc;
	t_cmd	*cmdv;
}	t_cmdtab;


typedef struct s_mshell
{
	char	exit_status;
	char	**env;
}	t_mshell;


//Unit tests, remove before pushing project for grading
char **ms_parse_input(char *input);
void ms_free_args(char **args);
int ms_execute(char **args);
int test_main();

//matrix
int		get_matrixlen(const char **matrix);
char	**expand_matrix(const char **matrix, const char *new_line);
char	**shrink_matrix(const char **matrix, const char *to_remove);
char	**dup_matrix(const char **matrix);
void	print_matrix(const char **matrix);
void	free_matrix(char **matrix);

//env
char	*ms_getenv(char const *var, char const **env);
void	init_env(char const *env[], t_mshell *mshell);
int		update_envp(const char *str, t_mshell *mshell);
int		is_valid_envp(const char *str, int n);

//pipes
t_cmd		*parse_pipe_cmd(char const *str, int *shift, int *i, t_mshell *mshell);
int 		exec_pipeline(int *argc, char **argv, t_mshell *mshell);
int			exec_cmd(t_cmd cmd, t_mshell *mshell);


// void		start_piping(t_list **envl, t_data *data);

//signals
void		signal_handler(int signo);
void		new_prompt_signal(void);

//parsing
t_cmdtab	*tokenize(char const *prompt, t_mshell *mshell);
//parsing utils
char		*ft_append(char *s1, char const *s2, int n);
int			nextquote(char const *s);
int			smartcount(char const *s, char const *sep, int trim_sep);

//freeing
void		free_cmdtab(t_cmdtab *cmd_tab);
char		**freetab(char **tab, int size);

char	*expand_cmd(char *name, char *path);

//redirections
int 		call_redirections(int argc, char **argv, t_cmd cmd, t_mshell *mshell);
// int			open_output_file(const char *filename, int flags, mode_t mode);
// void 		handle_input_redirection(const char **cmdv, int *cmdc, const char **input_file);
// void 		handle_output_redirection(const char **cmdv, int *cmdc, const char **output_file, const char **append_file)
// void 		handle_heredoc_redirection(const char **cmdv, int *cmdc, const char **delimiter);

#endif