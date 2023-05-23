/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:07:46 by jpilotte          #+#    #+#             */
/*   Updated: 2023/05/23 16:21:07 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ms_builtins.h"

//REMOVE DOUBLE QUOTE

int	nextquote(char const *s)
{
	int	i;

	i = 0;
	if (*s == '\'' || *s == '\"')
	{
		while (s[++i])
		{
			if (s[i] == *s)
				return (i);
		}
		return (perror("QUOTE_ERR"), -1);
	}
	return (0);
}

int	smartcount(char const *s, char const *sep, int trim_sep)
{
	int		count;
	char	*str;

	if (trim_sep)
		count = 0;
	else
		count = 1;
	str = (char *)s;
	while (*str)
	{
		if (nextquote(str) >= 0)
			str += nextquote(str);
		else
			return (-1);
		if (trim_sep)
		{
			if (!ft_strchr(sep, *str) && ft_strchr(sep, *(str + 1)))
				count++;
		}
		else if (ft_strchr(sep, *str))
			count++;
		str++;
	}
	return (count);
}

char	**freetab(char **tab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		*(tab[i]) = 0;
		free(tab[i]);
	}
	*tab = 0;
	free(tab);
	return (0);
}

char	**cmd_split(char const *s, char const sep, int const size)
{
	char	**tab;
	char	*str;
	int		len;
	int		count;

	str = (char *)s;
	tab = ft_calloc(size + 1, sizeof(*tab));
	if (!tab)
		return (perror("cmd_split: "), (char **) NULL);
	count = -1;
	while (++count < size)
	{
		len = 0;
		while (str[len] != sep && str[len])
			len += nextquote(str + len) + 1;
		tab[count] = ft_substr(str, 0, len);
		if (!tab[count])
			return (perror("cmd_split: "), freetab(tab, count));
		str += len + 1;
	}
	return (tab);
}

char	*arg_expand(char const *str, int len, t_list **envl) //40
{
	char	*arg;
	char	*temp;
	int		shift;
	int		i;

	arg = ft_calloc(1, sizeof(char));
	if (!arg)
		return (0);
	shift = 0;
	i = -1;
	while (++i < len - shift)
	{
		if (str[shift + i] == '\'')
		{
			shift++;
			while (str[shift + i] != '\'')
				i++;
			arg = ft_append(arg, str + shift, i);
			shift += i + 1;
			i = 0;
		}
		if (str[shift + i] == '$')
		{
			arg = ft_append(arg, str + shift, i);
			shift += i + 1;
			i = 0;
			while (!ft_strchr("$\t\n\v\f\r \0", str[shift + i]))
				i++;
			temp = ft_substr(str + shift, 0, i);
			if (get_envp(*envl, temp))
				arg = ft_append(arg, get_envp(*envl, temp),
						strlen(get_envp(*envl, temp)));
			free(temp);
			shift += i;
			i = -1;
		}
	}
	if (i <= len - shift)
		arg = ft_append(arg, str + shift, i);
	return (arg);
}

char	**arg_split(char const *s, char const *sep, int size, t_list **envl)
{
	char	**tab;
	char	*str;
	int		len;
	int		count;

	str = (char *)s;
	tab = ft_calloc(size + 1, sizeof(*tab));
	if (!tab)
		return (perror("arg_split: "), (char **)0);
	count = -1;
	while (++count < size)
	{
		len = 0;
		while (ft_strchr(sep, str[len]) && *str)
			str++;
		while (!ft_strchr(sep, str[len]) && str[len])
			len += nextquote(str + len) + 1;
		tab[count] = arg_expand(str, len, envl);
		if (!tab[count])
			return (perror("arg_split: "), freetab(tab, count));
		str += len + 1;
	}
	return (tab);
}

t_cmdtab	*tokenize(char *prompt, t_list **envl)
{
	t_cmdtab	*cmdtab;
	char		**cmdlines;
	int			i;

	cmdtab = ft_calloc(1, sizeof(t_cmdtab));
	cmdtab->cmdc = smartcount(prompt, "|", 0);
	cmdtab->cmdv = ft_calloc(cmdtab->cmdc, sizeof(t_cmd));
	cmdlines = cmd_split(prompt, '|', cmdtab->cmdc);
	i = -1;
	while (cmdlines[++i])
	{
		cmdtab->cmdv[i].argc = smartcount(cmdlines[i], WHTSPACES, 1);
		cmdtab->cmdv[i].argv = arg_split(cmdlines[i], WHTSPACES,
				cmdtab->cmdv[i].argc, envl);
		free(cmdlines[i]);
	// 	setredir(cmdtab->cmdv[i]);
	}
	free(cmdlines);
	return (cmdtab);
}

void	free_cmdtab(t_cmdtab *cmd_tab)
{
	int	cmd_i;
	int	arg_i;

	cmd_i = -1;
	while (++cmd_i < cmd_tab->cmdc)
	{
		arg_i = -1;
		while (++arg_i < cmd_tab->cmdv[cmd_i].argc)
			free(cmd_tab->cmdv[cmd_i].argv[arg_i]);
		free(cmd_tab->cmdv[cmd_i].argv);
	}
	free(cmd_tab->cmdv);
	free(cmd_tab);
}

int main(int ac, char **av, const char **ev)
{
	t_cmdtab	*cmd_tab;
	t_list	**envl;

//ENVL TEST
	envl = ft_calloc(1, sizeof(*envl));
	init_env(ev, envl);
//PROMPT TEST
	if (ac > 1)
		cmd_tab = tokenize(av[1], envl);
	else
	cmd_tab = tokenize("||  ls| . > \"  cat | echo $HOME AR $USER  	\"  humm | exit   42   54? |  echo a$HOMEaer$USER hellothere | echo '$USER'ef testsinglequote |", envl);
//DEBUG PRINT
	printf("cmdc: %d\n", cmd_tab->cmdc);
	for (size_t i = 0; i < cmd_tab->cmdc; i++)
	{
		printf("[%zu]%d: ", i, cmd_tab->cmdv[i].argc);
		for (size_t j = 0; cmd_tab->cmdv[i].argv[j]; j++)
			printf("%s,", cmd_tab->cmdv[i].argv[j]);
		printf("\b \n");
	}
// FREE
	free_cmdtab(cmd_tab);
	free_env(*envl);
	free(envl);
}

//TESTING
//gcc -g src/parsing.c src/env/env_var.c src/builtins/ft_export.c src/ft_append.c lib/libft/libft.a lib/readline/libreadline.a -lncursesa$HOMEaer$USERa$HOMEaer$USER