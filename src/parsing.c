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


char	*ft_append(char *s1, char const *s2, int n)
{
	char	*str;
	int		len[2];

	if (!s1)
		return (0);
	if (!s2)
		return (s1);
	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	if (n < len[1])
		len[1] = n;
	str = ft_calloc(len[0] + len[1] + 1, sizeof(*str));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, len[0] + 1);
	ft_strlcat(str, s2, len[0] + len[1] + 1);
	printf("bah %d\n", len[0] + len[1] + 1);
	if (*s1)
		free(s1);
	return (str);
}


char	**expand_matrix(char **matrix, char *new_line)
{
	int		size;
	char	**new_matrix;

	size = 0;
	while (matrix[size])
		size++;
	new_matrix = ft_calloc(size + 2, sizeof(*new_matrix));
	new_matrix[size] = ft_strdup(new_line);
	while (--size >= 0)
		new_matrix[size] = matrix[size];
	free(matrix);
	return (new_matrix);
}

#include <stdio.h>
#include <string.h>

t_cmd	*tokenize(char *prompt) {
	t_cmd	*cmds;
	int		chr_i;
	int		arg_i;
	int		cmd_i;

	chr_i = 0;
	arg_i = 0;
	cmd_i = 0;
	cmds = ft_calloc(99, sizeof(t_cmd));
	cmds[0].argv = ft_calloc(99, sizeof(char*));
	cmds[1].argv = ft_calloc(99, sizeof(char*));
	// cmds[2].argv = ft_calloc(99, sizeof(char*));
	// cmds[3].argv = ft_calloc(99, sizeof(char*));
	while (*prompt == ' ') //WHITESPACES
		prompt++;
	// while (prompt[chr_i])
	while (1)
	{
		// printf("%c", prompt[chr_i]);
		if (prompt[chr_i] == ' ' || prompt[chr_i] == 0)
		{
	// fflush(stdout);
			// prompt[chr_i] = 0;
			cmds[cmd_i].argv[arg_i] = ft_calloc(chr_i + 1, sizeof(char));
			ft_strlcpy(cmds[cmd_i].argv[arg_i], prompt, chr_i + 1);
	// printf("fill cmd:%d arg:%d with %s\n", cmd_i, arg_i, cmds[cmd_i].argv[arg_i]);
			prompt += chr_i;
			chr_i = 0;
			arg_i++;
			
			while (*prompt == ' ') //WHITESPACES
				prompt++;
			// continue;
		}
		if (prompt[chr_i] == '\'' || prompt[chr_i] == '\"')
		{
			printf("quote detected %s\n", prompt + chr_i + 1);
			char *temp = ft_strchr(prompt + chr_i + 1, prompt[chr_i]);
			if (!temp)
				return (perror("QUOTE_ERR"), (t_cmd*)NULL);
			else
			{
				int	t_len = strlen(prompt) - strlen(temp);
				// *temp = 0;
				cmds[cmd_i].argv[arg_i] = ft_calloc(t_len + 1, sizeof(char));
				ft_strlcpy(cmds[cmd_i].argv[arg_i], prompt, t_len + 1);
				while (prompt != temp)
					prompt++;
				
				// prompt += chr_i;
				chr_i = 0;
				arg_i++;
				
				while (*prompt == ' ') //WHITESPACES
					prompt++;
			}
		}
		if (prompt[chr_i] == '$')
		{
			// DUP before $
			// JOIN envar
			// continue
		}
		if (prompt[chr_i] == '|')
		{
			cmd_i++;
			prompt += chr_i + 1;
			chr_i = 0;
			arg_i = 0;
			
			while (*prompt == ' ') //WHITESPACES
				prompt++;
		}
		if (prompt[chr_i] == '<' || prompt[chr_i] == '>') // << < > >>
		{
			// select redirection
			// apply same loop til ' ', '|' or '><<>><' but overide redir value
			
			printf("REDIR!\n");
			while (*prompt == ' ') //WHITESPACES
				prompt++;
		}
		if (prompt[chr_i] == 0)
			break;
		chr_i++;
	}
	return (cmds);
}

int	smartcount(char const *s, char const *div, int trim)
{
	int		count;
	char	*str;

	count = 1;
	str = (char *)s;
	while (trim && *str && ft_strchr(div, *str))
		str++;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			str = ft_strchr(str + 1, *str);
				if (!str)
					return (perror("SQUOTEERR"), -1);
		}
		else if (ft_strchr(div, *str))
		{
			while (trim && str[1] && ft_strchr(div, str[1]))
				str++;
			if (str[1])
				count++;
		}
		str++;
	}
	
	return (count);
}

int	cmd_count(char const *s)
{
	int		count;
	char	*str;

	count = 1;
	str = (char *)s;
	while (*str && ft_strchr("\t\n\v\f\r ", *str))
		str++;
	if (*str == '|')
		return (perror("PARSE_ERR"), -1);
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			str = ft_strchr(str + 1, *str);
				if (!str)
					return (perror("QUOTE_ERR"), -1);
		}
		else if (*str == '|')
		{
			if (str[1] == '|' || !str[1])
				return (perror("PARSE_ERR"), -1);
			count++;
		}
		str++;
	}
	
	return (count);
}

t_cmdtab	*new_tokenize(char *prompt)
{
	t_cmdtab	*cmdtab;
	char		**cmdlines;
	int			i;

	cmdtab = ft_calloc(1, sizeof(t_cmdtab));
	// cmdtab->cmdc = smartcount(prompt, "|", 1);
	// cmdtab->cmdv = ft_calloc(cmdtab->cmdc, sizeof(t_cmd *));
	printf("%d\n", cmd_count(prompt));
	printf("%d\n", smartcount(prompt, "\t\n\v\f\r ", 1));
	// cmdlines = smartsplit(prompt, "|", 1);
	// i = 0;
	// while(cmdlines[i])
	// {
	// 	cmdtab->cmdv[i].argc = smartcount(cmdlines[i], "\t\n\v\f\r ", 0);
	// 	cmdtab->cmdv[i].argv = ft_calloc(cmdtab->cmdv[i].argc, sizeof(char *));
	// 	cmdtab->cmdv[i].argv = smartsplit(cmdlines[i], "\t\n\v\f\r ", 0);
	// 	setredir(cmdtab->cmdv[i]);
	// }
	return (cmdtab);
}

int main()
{
	// char	**old;
	// char	**new;
	// int		i;

	// old = ft_calloc(3, sizeof(old));
	// old[0] = ft_strdup("Hello There");
	// old[1] = ft_strdup("this is me,");
	// new = expand_matrix(old, "MARIO!!!");
	// i = 0;
	// while (new[i])
	// {
	// 	printf("%s\n", new[i]);
	// 	free(new[i]);
	// 	i++;
	// }
	// free(new);

	// char	*str;

	// str = ft_strdup("PRINTF: ");
	// printf("%s\n", ft_append(str, "and add this", 6));

	t_cmd	*cmd_tab;
	t_cmdtab	*cmdtab;
	int		cmd_i;
	int		arg_i;

	// cmd_tab = tokenize("echo test | export this is a test > bon | etpourfinir");
	// cmd_tab = tokenize("ls . > \"cat | echo ahah\" | exit 42 54?");
	cmdtab = new_tokenize("  ls . > \"  cat | echo ahah  \"   | exit   42   54? |  echo   | echo 'ohoh'  ");
	cmd_i = 0;
	// printf("\n");
	// while (cmd_tab + cmd_i != (t_cmd *)NULL)
	// {
	// printf("AH, %p\n", cmd_tab + cmd_i);
	// fflush(stdout);
	// 	arg_i = 0;
	// 	while (cmd_tab[cmd_i].argv[arg_i])
	// 	{
	// 		printf("%s, ", cmd_tab[cmd_i].argv[arg_i]);
	// 		arg_i++;
	// 	}
	// 	printf("\n");
	// 	cmd_i++;
	// }
}
