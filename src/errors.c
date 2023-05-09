/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpilotte <jpilotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:13:22 by jpilotte          #+#    #+#             */
/*   Updated: 2023/05/08 12:13:22 by jpilotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//exit and free all data
void exit_all(void)
{
	t_data *data;

	data = get_data();
	free(data->input);
	// free(data->cwd);
	free(data);
	exit(0);
}

void cwd_check(char *cwd)
{
	if (getcwd(cwd, PATH_MAX) == NULL) {
		perror("getcwd() error");
		return;
	}
}