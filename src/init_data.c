#include "../includes/minishell.h"


//init singleton for "global" use *replaces global variables
t_data *get_data(void)
{
	static t_data *data;

	data = NULL;

	if(data == NULL)
		data = (t_data *)malloc(sizeof(t_data));
	return (data);
}

void init_data(void)
{
	t_data *data;

	data = get_data();
	data->line = NULL;
	data->args = NULL;
}