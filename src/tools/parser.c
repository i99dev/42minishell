#include "../../include/minishell.h"

char	*ft_strtok(char *input, char delim)
{
	static char	*temp;
	char		*out;

	if (!input)
		input = temp;
	if (!input)
		return (NULL);
	while (*input)
	{
		if (*input == delim)
			input++;
		else
			break ;
	}
	if (!*input)
		return (NULL);
	out = input;
	while (*input)
	{
		if (*input == delim)
		{
			*input = '\0';
			temp = input + 1;
			return (out);
		}
		input++;
	}
	temp = input;
	return (out);
}

/*
	parses and splits input line into command table
	TODO:	support characters like "|", ">", "<", etc.
			handle double and single quotes
			fix tokenizer and return it.
*/
char	**init_command_table(char *input)
{
	char	*token;

	printf("--------------\n");
	printf("COMMAND TABLE\n");
	token = ft_strtok(input, ' ');
	while (token)
	{
		printf("%s\n", token);
		token = ft_strtok(NULL, ' ');
	}
	printf("--------------\n");
	return (ft_split(input, ' '));
}
