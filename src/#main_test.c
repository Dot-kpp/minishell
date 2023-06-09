/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:08:47 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/20 13:08:47 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ms_builtins.h"

int ft_isspacesonly(const char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (!ft_strchr("\t\n\v\f\r ", str[i]))
			return (0);
	}
	return (1);
}

//start running minishell overlay
static void	minishell(t_mshell *mshell, const char *prompt)
{
	t_cmdtab	*cmd_tab;
	// char		*prompt;
	// char		waiting_prompt[PATH_MAX];

	// while (1)
	// {
		int	i;

		// cwd_check(ft_getenv("PWD", (const char **)mshell->env));
		// getcwd(waiting_prompt, PATH_MAX);
		// if (!mshell->exit_status)
		// 	ft_strlcat(waiting_prompt, "\001\033[1;96m\002 % \033[0;39m\001", PATH_MAX);
		// else
		// 	ft_strlcat(waiting_prompt, "\001\033[1;91m\002 % \033[0;39m\001", PATH_MAX);
		new_prompt_signal();
		// prompt = readline((const char *)waiting_prompt);
		// if (prompt == NULL) // If input is NULL, user has pressed Ctrl-D or EOF has been reached
		// 	return ;
		if (ft_strlen(prompt) == 0 || ft_isspacesonly(prompt))// If input is empty, continue to next loop iteration
		{
			// free(prompt);
			return ;
		}
		// add_history(prompt); // Add input to history
		cmd_tab = tokenize(prompt, mshell); //PARSING
		if (!cmd_tab)
		{
		// free_cmdtab(cmd_tab);
			// free(prompt);
			mshell->exit_status = -1;
			return;
		}
		i = -1;
		while (++i < cmd_tab->cmdc) // EXEC
		{
			if(cmd_tab->cmdc > 1)
			{
				exec_pipeline(cmd_tab, mshell);
				return;
			}
			else
				mshell->exit_status = exec_cmd(cmd_tab->cmdv[i], mshell);
		}
		// continue;
		free_cmdtab(cmd_tab);
		// free(prompt);
	// }
}

int	main(int ac, char const **av, char const **envp)
{
	t_mshell	mshell;

	(void)ac;
	(void)av;
	init_env(envp, &mshell);
	minishell(&mshell, av[2]);
	// exit_all();
	clear_history();
	free_matrix(mshell.env);
	return (0);
}
