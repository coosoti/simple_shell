#include "shell.h"

/**
 * error_handler - write an error message if file is not found
 * @argv: the array of passed in function argument strings
 * @ar: array of tokens entered by the user
 * @cmdcount_int: the number of commands entered
 * @line: user input
 * @nline: user input without the nline character
 */

void error_handler(char **argv, char **ar, int cmdcount_int, char *line,
		   char *nline)
{
	char *num;

	num = print_int(cmdcount_int);
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, num, _strlen(num));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, ar[0], _strlen(ar[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "not found\n", 10);
	free(num);
	free_all(line, nline, ar);
	exit(0);
}
