#include "../includes/minishell.h"

//exit and free all data
void exit_all(void)
{
	t_data *data;

	data = get_data();
	free(data);
}