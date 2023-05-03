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

//ft_strcmp
int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while(s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return(s1[i] - s2[i]);
}

//link libft functions not working, needs to be looked into
void parse_args(char **av)
{
    int i;
    int j;
    int k;
    char **args;

    i = 0;
    j = 0;
    k = 0;
    args = (char **)malloc(sizeof(char *) * 1024);

    while (av[i])
    {
        if (ft_strcmp(av[i], ";") == 0)
        {
            args[j][k] = '\0';
            j++;
            k = 0;
        }
        else
        {
            args[j] = (char *)malloc(sizeof(char) * (strlen(av[i]) + 1));
            strcpy(args[j], av[i]);
            j++;
        }
        i++;
    }
    args[j] = NULL;
    i = 0;

    while (args[i])
    {
        printf("%s\n", args[i]);
        free(args[i]);
        i++;
    }
    free(args);
}




//tester
int main(int ac, char **av)
{
    if (ac > 1)
        parse_args(av);
    return(0);
}