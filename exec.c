#include "shell.h"

/**
 * execute_cmd - func to execute a line of code in the shell
 * @ar: array of strings(commands) to be executed
 * @env: environment variable
 * @av: array of cmd line argument strings
 * @line: user input
 * @nline: user input with newline truncated
 * @cmd_count: number of user input commands
 * Return: 0 on success, otherwise -1 on failure
 */

int execute_cmd(char **ar, char **env, char **av, char *line, char *nline,
		int cmd_count)
{
	pid_t my_pid;
	char *concat;
	int signal;
	struct stat status;

	if (ar == NULL || *ar == NULL || av == NULL || *av == NULL)
		return (-1);
	if (env == NULL || *env == NULL)
		return (-1);
	if (checkBuiltins(ar, env, line, nline, cmd_count) == 0)
		return (0);
	my_pid = fork();
	if (my_pid == -1)
	{
		write(STDOUT_FILENO, "Error forking", 13);
		return (-1);
	}
	if (my_pid == 0)
	{
		if (ar[0][0] == '/')
		{
			if (stat(ar[0], &status) == -1)
				error_handler(av, ar, cmd_count, line, nline);
			if (access(ar[0], X_OK) == -1)
				error_handler(av, ar, cmd_count, line, nline);
			execve(ar[0], ar, NULL);
		}
		else
		{
			concat = path_handler(ar[0], env);
			if (concat == NULL)
				error_handler(av, ar, cmd_count, line, nline);
			else
				execve(concat, ar, NULL);
		}
	}
	else
		wait(&signal);
	return (0);
}
