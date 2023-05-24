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

//start running minishell overlay
static void minishell(t_list **envl)
{
	// t_data		*data;
	t_cmdtab	*cmd_tab;
	int			ret = 0;
	char		*prompt;
	char		waiting_prompt[PATH_MAX];

	// data = get_data();
	while (1) {
		cwd_check(get_envp(*envl, "PWD"));
		ft_strlcpy(waiting_prompt, get_envp(*envl, "PWD"), PATH_MAX);
		ft_strlcat(waiting_prompt, "\001\033[1;96m\002 % \033[0;39m\001", PATH_MAX);
		new_prompt_signal();
		prompt = readline((const char *)waiting_prompt);
		// If input is NULL, user has pressed Ctrl-D or EOF has been reached
		if (prompt == NULL) {
			printf("\n");
			break;
		}
		// If input is empty, continue to next loop iteration
		if (ft_strlen(prompt) == 0) {
			free(prompt);
			continue;
		}
		// Add input to history
		add_history(prompt);
		
		//PARSING
		cmd_tab = tokenize(prompt, envl);

		// EXEC
		// CHECK IF BUILTIN
		ret = call_builtin(cmd_tab->cmdv[0].argc, (const char **)cmd_tab->cmdv[0].argv, envl);
		if (ret != -1)
		{
			free_cmdtab(cmd_tab);
			continue;
		}
		// start_piping(envl, data);
		// free_input();
		free_cmdtab(cmd_tab);
	}
}

int main(int ac, char const **av, char const **envp)
{
	t_list		*envl;
	(void)ac;
	(void)av;

	envl = 0;
	init_env(envp, &envl);
	// init_data();
	minishell(&envl);
	exit_all();
	clear_history();

	free_env(envl);
	
	return (0);
}
