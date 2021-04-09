#include "shell.h"

/**
 * shellPrompt - func to prompt of the shell
 *
 */

void shellPrompt(void)
{
	unsigned int i;
	char prompt[] =  "($ )";

	if (isatty(STDIN_FILENO))
	{
		i = 0;
		while (prompt[i] != '\0')
		{
			_putchar(prompt[i]);
			i++;
		}
	}
}
