/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:07:46 by jpilotte          #+#    #+#             */
/*   Updated: 2023/05/03 10:52:44 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



// 1- Parse the user input to identify the command and its arguments.

// 2- Check if the command is a built-in shell command. If it is, execute the built-in command directly.

// 3- If the command is not a built-in command, search for the executable file in the directories listed in the PATH environment variable. The PATH variable is a colon-separated list of directories in which the shell will look for executable files.

// 4- If the command is specified with a relative or absolute path, use that path to locate the executable file.

// 5 - If the executable file is found, execute it with the specified arguments. If the file is not found, print an error message and return control to the shell.

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while(s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return(s1[i] - s2[i]);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}



//link libft functions not working, needs to be looked into
void parse_args(char *input)
{
    int i;
    int j;
    int k;
    char **args;

    i = 0;
    j = 0;
    k = 0;
    args = (char **)malloc(sizeof(char *) * 1024);

    while (input[i])
    {
        if (ft_strcmp(input[i], ";") == 0)
        {
            args[j][k] = '\0';
            j++;
            k = 0;
        }
        else
        {
            args[j] = (char *)malloc(sizeof(char) * (ft_strlen(input[i]) + 1));
            ft_strcpy(args[j], input[i]);
            j++;
        }
        i++;
    }
    args[j] = NULL;
    i = 0;
    free(args);
}
