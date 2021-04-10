#include "shell.h"

/**
 * no_ferror - write an error message if file is not found
 * @argv: the array of passed in function argument strings
 * @arr: array of tokens entered by the user
 * @cmd_count: the number of commands entered
 * @input: user input
 * @newline: user input without the newline character
 */

void no_ferror(char **argv, char **arr, int cmd_count, char *input, char *newline)
{
	char *no;

	no = print_int(cmd_count);
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, no, _strlen(no));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, arr[0], _strlen(arr[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "not found\n", 10);
	free(no);
	free_all(input, newline, arr);
	exit(0);
}
