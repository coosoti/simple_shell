#include "shell.h"

/**
 * exit_hnadler - handles exit builtin
 * @arr: array of strings commands for execution
 * @input: user input
 * @newline: user input with newline truncated
 * @cmd_count: no of commands entered by the user
 * Return: 0 on success, or exit code specified by user
 */

int exit_handler(char **arr, char *input, char *newline, int cmd_count)
{
	int num, j = 0;
	char *cmd_countint;

	if (arr[1] == NULL)
	{
		free_all(input, newline, arr);
		_exit(0);
	}

	else
	{
		num = _atoi(arr[1]);
		if (num == -1)
		{
			cmd_countint = print_int(cmd_count);
			write(STDERR_FILENO, "./hsh: ", 7);
			write(STDERR_FILENO, cmd_countint, _strlen(cmd_countint));
			write(STDERR_FILENO, ": exit: Illegal number: ", 24);
			while (arr[1][j] != '\0')
				j++;
			write(STDOUT_FILENO, arr[1], j);
			write(STDOUT_FILENO, "\n", 1);
			return (0);
		}
		free_all(input, newline, arr);
		exit(num);
	}
}

/**
 * cd_handler - handles the cd builtin
 * @arr:  array of command line strings
 * @env: environment variable
 * Return: 0 on success
 */
int cd_handler(char **arr, char **env)
{
	int i = 0;
	char currentDir[1024];
	char *newDir;

	if (arr[1] == NULL)
	{
		if (chdir(_getenv("HOME", env)) == -1)
		{
			perror("./hsh");
			write(STDERR_FILENO, "cd: can't cd to home\n", 21);
		}
	}
	else
	{
		getcwd(currentDir, 1024);
		while (currentDir[i] != '\0')
			i++;
		currentDir[i++] = '/';
		currentDir[i] = '\0';
		newDir = strcat(currentDir, arr[1]);
		if (newDir == NULL)
			return (0);
		if (chdir(newDir) == -1)
		{
			perror("./hsh");
			write(STDERR_FILENO, "can't cd into directory\n", 24);
		}
		free(newDir);
	}
	return (0);
}

/**
 * env_handler - handles the env builtin
 * @env: environment variable
 * Return: 0 on success
 */

int env_handler(char **env)
{
	int i, len = 0;

	while (env[i] != NULL)
	{
		len = _strlen(env[i]);
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}

/**
 * checkBuiltin - check if command passed exist in the shell
 * @arr: array of strings to execute
 * @env: the environment variable
 * @input: user input
 * @newline: user input without newline character
 * @cmd_count: number of commands entered by the user
 *
 * Return: 0 when builtin command is found, 1 when builtin not found
 */

int checkBuiltin(char **arr, char **env, char *input, char *newline, int cmd_count)
{
	if (arr == NULL || *arr == NULL)
		return (1);
	if (env == NULL || *env == NULL)
		return (1);
	if (_strcmp((arr[0]), "exit") == 0)
		return (exit_handler(arr, input, newline, cmd_count));
	else if (_strcmp((arr[0]), "cd") == 0)
		return (cd_handler(arr, env));
	else if (_strcmp((arr[0]), "env") == 0)
		return (env_handler(env));
	else
		return (1);
}
