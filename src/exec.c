/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:23:01 by fgeslin           #+#    #+#             */
/*   Updated: 2023/05/29 11:41:07 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 1- Parse the user input to identify the command and its arguments.

// 2- Check if the command is a built-in shell command. If it is, execute the built-in command directly.

// 3- If the command is not a built-in command, search for the executable file in the directories listed in the PATH environment variable. The PATH variable is a colon-separated list of directories in which the shell will look for executable files.

// 4- If the command is specified with a relative or absolute path, use that path to locate the executable file.

// 5 - If the executable file is found, execute it with the specified arguments. If the file is not found, print an error message and return control to the shell.

#include "../includes/minishell.h"
#include "../includes/ms_builtins.h"

int exec_cmd(t_cmd cmd)
{
    (void)cmd;
    return (0);
}