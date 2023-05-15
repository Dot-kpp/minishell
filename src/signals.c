/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:13:50 by jpilotte          #+#    #+#             */
/*   Updated: 2023/05/08 12:13:50 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// #include "../lib/readline/readline.h"
# include <sys/ioctl.h>

// //signal handler 

void signal_handler(int signo)
{
	// // Handle signals here
	if (signo == SIGINT)
	{
		// printf("SIG!\n");
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void new_prompt_signal(void)
{
    struct sigaction sa;

    printf("new_prompt_signal!\n");
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction() error");
        return;
    }
    signal(SIGQUIT, SIG_IGN);
}
