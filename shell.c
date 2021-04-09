#include "shell.h"

/**
 * tokenize - splits user input into tokens and stores into array
 * @input: input string to split
 *
 * Return: array of strings(tokens)
 */

char **tokenize(char *input)
{
	int i = 0;
	int t_count = 0;
	char **t_array;
	char *token, *t_copy;

	if (input == NULL)
		return (NULL);
	while (*(input + i) != '\0')
	{
		if (input[i] != ' ' && (input[i + 1] == ' ' || input[i + 1] == '\0'
				       || input[i + 1] == '\t'))
			t_count++;
		i++;
	}

	i = 0;
	t_array = malloc(sizeof(char *) * (t_count + 1));
	if (t_array == NULL)
		return (NULL);
	token = strtok(input, DELIMITER);
	while (token != NULL)
	{
		t_copy = _strdup(token);
		if (t_copy == NULL)
		{
			free(t_array);
			return (NULL);
		}
		*(t_array + i) = t_copy;
		token = strtok(NULL, DELIMITER);
		i++;
	}
	*(t_array + i) = NULL;
	return (t_array);
}
