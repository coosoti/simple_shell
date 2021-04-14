#include "shell.h"

/**
 * execute - func to execute a line of code in the shell
 * @arr: array of strings(commands) to be executed
 * @env: environment variable
 * @av: array of cmd line argument strings
 * @line: user input
 * @nline: user input with newline truncated
 * @cmd_count: number of user input commands
 * Return: 0 on success, otherwise -1 on failure
 */

int execute(char **arr, char **env, char **av, char *line, char *nline, int cmd_count)
{
	pid_t _pid;
	struct stat status;
	int signal;
	char *abs_path;

	if (arr == NULL || *arr == NULL || av == NULL || *av == NULL)
		return (-1);
	if (env == NULL || *env == NULL)
		return (-1);
	if (checkBuiltin(arr, env, line, nline, cmd_count) == 0)
		return (0);

	_pid = fork();

	if (_pid == -1)
	{
		write(STDOUT_FILENO, "error", 13);
		return (-1);
	}
	if (_pid == 0)
	{
		if (arr[0][0] == '/')
		{
			if (stat(arr[0], &status) == -1)
				no_ferror(av, arr, cmd_count, line, nline);
			if (access(arr[0], X_OK) == -1)
				no_ferror(av, arr, cmd_count, line, nline);
			execve(arr[0], arr, NULL);

		}
		else
		{
			abs_path = _path(arr[0], env);
			if (abs_path == NULL)
				no_ferror(av, arr, cmd_count, line, nline);
			else
				execve(abs_path, arr, NULL);
		}
	}
	else
		wait(&signal);
	return (0);
}
