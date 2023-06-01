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

int		call_builtin(int argc, char const *argv[], t_mshell *mshell);

int		ms_cd(int argc, char const *argv[], t_mshell *mshell);
int		ms_echo(int argc, char const *argv[], t_mshell *mshell);
int		ms_env(int argc, char const *argv[], t_mshell *mshell);
int		ms_exit(int argc, char const *argv[], t_mshell *mshell);
int		ms_export(int argc, char const *argv[], t_mshell *mshell);
int		ms_pwd(int argc, char const *argv[], t_mshell *mshell);
int		ms_unset(int argc, char const *argv[], t_mshell *mshell);

#endif