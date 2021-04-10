#include "shell.h"

/**
 * ctrlc_handler - Ctrl+C handler
 * @signum: signal number received
 * Return: void
 */

void ctrlc_handler(int signum)
{
	(void)signum;

	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * ctrld_handler - Ctrl+D handler
 * @input: the main line buffer to free
 * Return: 0 on success
 */

int ctrld_handler(char *input)
{
	free(input);
	if (isatty(STDIN_FILENO) == 1)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
