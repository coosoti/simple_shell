#include <stdio.h>
#include <unistd.h>


/**
 * main- print the prompt of shell
 * Return: void
 **/
void main()
{
	if (isatty(STDIN_FILENO))
	{
		putchar(' ');
	}
}
