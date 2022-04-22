#include "../../include/minishell.h"
/*
	splits input line into command table.
	TODO: support characters like "|", ">", "<", etc.
*/

char	**init_command_table(char *input)
{
	return (ft_split(input, ' '));
}
