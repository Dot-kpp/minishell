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

# define MATRIX const char **

# define MAX_PATH_LENGTH 1024
# define MAX_ARGS 128

# define WHTSPACES "\t\n\v\f\r \0"

typedef struct s_cmd
{
	int		argc;
	char	**argv;
	int		redirc;
	char	**redirs;
}	t_cmd;

typedef struct s_cmdtab
{
	int		cmdc;
	t_cmd	*cmdv;
}	t_cmdtab;

typedef struct s_mshell
{
	unsigned char	exit_status;
	char			**env;
}	t_mshell;

//Unit tests, remove before pushing project for grading
char		**ms_parse_input(char *input);
void		ms_free_args(char **args);
int			ms_execute(char **args);
int			test_main(void);

//matrix
int			get_matrixlen(const char **matrix);
char		**expand_matrix(const char **matrix, char *new_line);
char		**shrink_matrix(const char **matrix, const char *to_remove);
char		**dup_matrix(const char **matrix);
void		print_matrix(const char **matrix);
void		print_sortedmatrix(char const **matrix);
void		free_matrix(char **matrix);

//env
char		*ms_getenv(char const *var, char const **env);
void		init_env(char const *env[], t_mshell *mshell);
int			update_envp(const char *str, t_mshell *mshell);
int			is_valid_envp(const char *str, int n);

//pipes
t_cmd		*parse_pipe_cmd(char const *str, int *shift, int *i, t_mshell *ms);
int			exec_pipeline(t_cmdtab *cmd_tab, t_mshell *mshell);
int			exec_cmd(t_cmd cmd, t_mshell *mshell);
// char		*expand_cmd(char *name, char *path);

//signals
void		signal_handler(int signo);
void		new_prompt_signal(void);

//parsing
t_cmdtab	*tokenize(char const *prompt, t_mshell *mshell);
char		**cmd_split(char const *s);
char		**arg_split(char const *s, t_mshell *mshell);
char		**redir_split(char const *s, t_mshell *mshell);
char		*arg_quotes(char const *str, int len, t_mshell *mshell);
//parsing utils
char		*ft_append(char *s1, char const *s2, int n);
int			nextquote(char const *s);
int			smartcount(char const *s, char const *sep, int trim_sep);
int 		ft_perror(int count, ...);

//freeing
void		free_cmdtab(t_cmdtab *cmd_tab);

//redirections
int			call_redirections(t_cmd *cmd, t_mshell *mshell);
void 		handle_heredoc_redirection(char **argv, int *argc, char **delimiter);

#endif