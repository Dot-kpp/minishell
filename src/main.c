/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:08:47 by fgeslin           #+#    #+#             */
/*   Updated: 2023/06/13 15:51:11 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ms_builtins.h"

static int	ft_isspacesonly(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_strchr("\t\n\v\f\r ", str[i]))
			return (0);
	}
	return (1);
}

static int	exec_prompt(char *prompt, t_mshell *mshell)
{
	t_cmdtab	*cmdtab;

	cmdtab = tokenize(prompt, mshell);
	if (!cmdtab)
	{
		mshell->exit_status = 1;
		return (0);
	}
	mshell->exit_status = exec_pipeline(cmdtab, mshell);
	free_cmdtab(cmdtab);
	return (1);
}

//start running minishell overlay
static void	minishell(t_mshell *mshell)
{
	char		*prompt;
	char		waiting_prompt[PATH_MAX];

	while (1)
	{
		getcwd(waiting_prompt, PATH_MAX);
		if (!mshell->exit_status)
			ft_strlcat(waiting_prompt,
				"\001\033[1;96m\002 % \033[0;39m\001", PATH_MAX);
		else
			ft_strlcat(waiting_prompt,
				"\001\033[1;91m\002 % \033[0;39m\001", PATH_MAX);
		new_prompt_signal();
		prompt = readline((const char *)waiting_prompt);
		if (prompt == NULL)
			return ;
		if (ft_strlen(prompt) == 0 || ft_isspacesonly(prompt))
		{
			free(prompt);
			continue ;
		}
		if (exec_prompt(prompt, mshell))
			add_history(prompt);
		free(prompt);
	}
}

int	main(int ac, char const **av, char const **envp)
{
	t_mshell	mshell;

	(void)ac;
	(void)av;
	init_env(envp, &mshell);
	minishell(&mshell);
	clear_history();
	free_matrix(mshell.env);
	return (0);
}
