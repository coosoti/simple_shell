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
	char *line, *newline;
	size_t len = 0;
	ssize_t chars;
	char **t_array;

	(void)ac, (void)av;
	while (1)
	{
		line = NULL;
		len = 0;
		cmd_count++;
		if (isatty(STDIN_FILENO) == 1)
			shellPrompt();
		signal(SIGINT, ctrlc_handler);
		chars = getline(&line, &len, stdin);
		if (chars == EOF || chars == -1)
			return (ctrld_handler(line));
		if (line[0] == '\n')
		{
			free(line);
			continue;
		}
		newline = _realloc(line);
		if (newline == NULL)
		{
			free(line);
			return (0);
		}
		t_array = tokenize(newline);
		if (t_array == NULL)
		{
			free(line);
			free(newline);
			return (0);
		}
		execute(t_array, env, av, line, newline, cmd_count);
		free_all(line, newline, t_array);
	}
}

/**
 * tokenize - splits user input into tokens and stores into array
 * @line: input string to split
 *
 * Return: array of strings(tokens)
 */

char **tokenize(char *line)
{
	int i = 0;
	int t_count = 0;
	char **t_array;
	char *token, *t_copy;

	if (line == NULL)
		return (NULL);
	while (*(line + i) != '\0')
	{
		if (line[i] != ' ' && (line[i + 1] == ' ' || line[i + 1] == '\0'
				       || line[i + 1] == '\t'))
			t_count++;
		i++;
	}

	i = 0;
	t_array = malloc(sizeof(char *) * (t_count + 1));
	if (t_array == NULL)
		return (NULL);
	token = strtok(line, DELIMITERS);
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
