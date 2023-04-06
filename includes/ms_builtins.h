/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:48 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/05 12:08:37 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_BUILTINS_H
# define MSHELL_BUILTINS_H

void 	ft_cd(int argc, char const *argv[]);
void 	ft_echo(int argc, char const *argv[]);
void	ft_env(char const *env[]);
void	ft_exit(void f(void*), void *param);
void	ft_export(char const *args[]);
int 	ft_pwd(int argc);
void	ft_unset(char const *args[]);

char	*ft_strnrpl(char const *str, char const *pst, char const *cpy, int n);

#endif