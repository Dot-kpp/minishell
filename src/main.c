#include "../includes/minishell.h"



// void read_line(void)
// {
// 	char *line = NULL;
// 	size_t bufsize = 0;
// 	getline(&line, &bufsize, stdin);
// 	return (line);
// }

// int main(int argc, char **argv, char **envp)
// {
// 	char *line;
// 	char **args;
// 	int status;

// 	while (1)
// 	{
// 		printf("minishell$ ");
// 		line = read_line();
// 		args = split_line(line);
// 		status = execute(args);

// 		free(line);
// 		free(args);
// 	}
// 	return (0);
// }



void ft_freestrarr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int exec_command(char *command)
{
	char	**args;
	int		ret;

	args = ft_strsplit(command, ' ');
	if (ft_isemptystr(args[0], 0))
	{
		ft_freestrarr(args);
		return (0);
	}
	ret = exec_builtin(args);
	if (ret == -1)
	{
		ft_freestrarr(args);
		return (-1);
	}
	else if (ret == 0)
	{
		ret = exec_bin(args);
		if (ret == -1)
		{
			ft_freestrarr(args);
			return (-1);
		}
	}
	ft_freestrarr(args);
	return (0);
}


int exec_commands(char **commands)
{
	int		i;
	int		ret;

	i = 0;
	while (commands[i])
	{
		ret = exec_command(commands[i]);
		if (ret == -1)
			return (-1);
		i++;
	}
	return (0);
}

//ft_countwords

//ft_wordlen


char **ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;
	int		k;

	if (!s || !(arr = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		k = 0;
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		if (!(arr[j] = (char *)malloc(sizeof(char) * (ft_wordlen(s + i, c) + 1))))
			return (NULL);
		while (s[i] && s[i] != c)
			arr[j][k++] = s[i++];
		arr[j++][k] = '\0';
	}
	arr[j] = NULL;

}

int ftisemptystr(char *str, int free_str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			if (free_str)
				free(str);
			return (0);
		}
		i++;
	}
	if (free_str)
		free(str);
	return (1);
}

char *get_input(char **input)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = get_next_line(0, &line);
	if (ret == -1)
	{
		ft_putstr("Error: get_next_line() failed.\n");
		exit(1);
	}
	else if (ret == 0)
	{
		ft_putstr("exit");
		exit(0);
	}
	*input = line;
	return (line);
}

char *get_envv(char *name)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = ft_strlen(name);
	while (g_envv[i])
	{
		if (ft_strncmp(g_envv[i], name, len) == 0 && g_envv[i][len] == '=')
		{
			tmp = ft_strdup(g_envv[i] + len + 1);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

void display_prompt_msg(void)
{
	char	*cwd;
	char	*home;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	home = get_envv("HOME");
	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		tmp = ft_strjoin("~", cwd + ft_strlen(home));
		free(cwd);
		cwd = tmp;
	}
	printf("%s$ ", cwd);
	free(cwd);
	free(home);
}

void init_envv(int ac, char **av, char **envv)
{
	int		i;
	int		len;

	(void)ac;
	(void)av;
	len = ft_strlen(envv);
	g_envv = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		g_envv[i] = ft_strdup(envv[i]);
		i++;
	}
	g_envv[i] = NULL;
}

int				main(int ac, char **av, char **envv)
{
	char	*input;
	int		ret;
	char	**commands;

	init_envv(ac, av, envv);
	while (1)
	{
		display_prompt_msg();
		signal(SIGINT, signal_handler);
		get_input(&input);
		if (ft_isemptystr(input, 1))
		{
			free(input);
			continue ;
		}
		commands = ft_strsplit(input, ';');
		free(input);
		ret = exec_commands(commands);
		ft_freestrarr(commands);
		if (ret == -1)
			break ;
	}
	ft_freestrarr(g_envv);
	return (0);
}
