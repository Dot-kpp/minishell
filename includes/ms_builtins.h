/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:48 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/17 14:16:46 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_BUILTINS_H
# define MSHELL_BUILTINS_H

typedef	void (*Fun) (int argc, char const *argv[]);

typedef struct	s_builtin
{
	char	*name;
	Fun		fun;
}	t_builtin;

typedef struct	s_ms_env
{
	char	*name;
	char	*value;
}	t_ms_env;


void	ft_cd(int argc, char const *argv[]);
void	ft_echo(int argc, char const *argv[]);
void	ft_env(t_list *envl);
void	ft_exit(void f(void*), void *param);
void	ft_export(char const *name, t_list **envl_ptr);
int 	ft_pwd(int argc);
void	ft_unset(char const *name, t_list **envl_ptr);

// t_list	*get_envl(t_list *new_envl);
void	free_env_content(void *arg);
void	free_env(t_list *envl);
void	init_env(char const *env[], t_list **envl);
char	*get_envp(t_list *envl, char const *name);

char	*ft_strnrpl(char const *str, char const *pst, char const *cpy, int n);

#endif