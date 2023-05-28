/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:48 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/21 14:44:14 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_BUILTINS_H
# define MSHELL_BUILTINS_H

# include "minishell.h"

typedef struct	s_ms_env
{
	char	*name;
	char	*value;
}	t_ms_env;


int		call_builtin(int argc, char const *argv[], t_list **envl);

int		ft_cd(int argc, char const *argv[], t_list **envl);
int		ft_echo(int argc, char const *argv[], t_list **envl);
int		ft_env(int argc, char const *argv[], t_list **envl);
int		ft_exit(int argc, char const *argv[], t_list **envl);
int		ft_export(int argc, char const *argv[], t_list **envl);
int		ft_pwd(int argc, char const *argv[], t_list **envl);
int		ft_unset(int argc, char const *argv[], t_list **envl);

// t_list	*get_envl(t_list *new_envl);
void	free_env_content(void *arg);
void	free_env(t_list *envl);
void	init_env(char const *env[], t_list **envl);
char	*get_envp(t_list *envl, char const *name);

char	*ft_strnrpl(char const *str, char const *pst, char const *cpy, int n);

#endif