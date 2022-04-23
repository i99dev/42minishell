#include "../../include/minishell.h"
/*
	parses and splits input line into command table
	TODO:	support characters like "|", ">", "<", etc.
			handle double and single quotes
*/

char	**init_command_table(char *input)
{
	return (ft_split(input, ' '));
}
