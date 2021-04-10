#include "shell.h"
#define DELIMITERS " \t\0"

/**
 * main - entry point
 * @ac: number of arguments passed
 * @av: array of strings of arguments passed
 * @env: the current environment
 * Return: 0 when EOF is reached - user presses Ctrl + D
 */

int main(int ac, char **av, char **env)
{
	int cmd_count = 0;
	char *input, *newline;
	size_t len = 0;
	ssize_t chars;
	char **t_array;

	(void)ac, (void)av;
	while (1)
	{
		input = NULL;
		len = 0;
		cmd_count++;
		if (isatty(STDIN_FILENO) == 1)
			shellPrompt();
		signal(SIGINT, ctrlc_handler);
		chars = getline(&input, &len, stdin);
		if (chars == EOF || chars == -1)
			return (ctrld_handler(input));
		if (input[0] == '\n')
		{
			free(input);
			continue;
		}
		newline = _realloc2(input);
		if (newline == NULL)
		{
			free(input);
			return (0);
		}
		t_array = tokenize(newline);
		if (t_array == NULL)
		{
			free(input);
			free(newline);
			return (0);
		}
		execute(t_array, env, av, input, newline, cmd_count);
		free_all(input, newline, t_array);
	}
}

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
	token = strtok(input, DELIMITERS);
	while (token != NULL)
	{
		t_copy = _strdup(token);
		if (t_copy == NULL)
		{
			free(t_array);
			return (NULL);
		}
		*(t_array + i) = t_copy;
		token = strtok(NULL, DELIMITERS);
		i++;
	}
	*(t_array + i) = NULL;
	return (t_array);
}
