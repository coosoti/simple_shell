#include "shell.h"

/**
 * _realloc - reallocates memory for char
 * @ptr: pointer to an array
 * Return: pointer to new memory
 */
char *_realloc(char *ptr)
{
	int i = 0;
	char *newptr;

	if (ptr == NULL)
		return (NULL);

	while (*(ptr + i) != '\n')
		i++;

	newptr = malloc(sizeof(char) * i + 1);
	if (newptr == NULL)
		return (NULL);
	i = 0;
	while (*(ptr + i) != '\n')
	{
		*(newptr + i) = *(ptr + i);
		i++;
	}
	*(newptr + i) = '\0';
	return (newptr);
}

/**
 * free_list - frees a linked_t list
 * @head: head of the linked list
 * Return: void
 */

void free_list(linked_t *head)
{
	linked_t *nextnode;

	while (head != NULL)
	{
		nextnode = head->next;
		free(head->directory);
		free(head);
		head = nextnode;
	}
}

/**
 * free_tokens - frees the tokens in the t_array array
 * @t_array: array of tokens
 * Return: void
 */

void free_tokens(char **t_array)
{
	int i = 0;

	while (t_array[i] != NULL)
	{
		free(t_array[i]);
		i++;
	}
	free(t_array[i]);
}


/**
 * free_all - frees all of the variables used
 * @line: the original line entered by user
 * @newline: user input without newline char
 * @t_array: array of tokens
 * Return: void
 */
void free_all(char *line, char *newline, char **t_array)
{
	free_tokens(t_array);
	free(line);
	free(newline);
	free(t_array);
}
