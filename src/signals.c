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
#include "../lib/readline/readline.h"

// //signal handler 

void signal_handler(int signo)
{
	// Handle signals here
    (void)signo;
	rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void new_prompt_signal(void)
{
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction() error");
        return;
    }
}
