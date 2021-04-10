#include "shell.h"

/**
 * _realloc - reallocates memory for char**
 * @p: pointer to an array
 * @n: number of elements to add/subtract
 * Return: pointer to new memory
 */
char **_realloc(char **p, int n)
{
	int i = 0;
	char **newptr;
	int new;

	if (p == NULL || *p == NULL)
		return (NULL);

	while (*(p + i) != NULL)
		i++;

	new = i + n;
	newptr = malloc(sizeof(char *) * new + 1);
	if (newptr == NULL)
		return (NULL);
	i = 0;
	while (*(p + i) != NULL)
	{
		*(newptr + i) = *(p + i);
		i++;
	}
	*(newptr + i) = NULL;
	return (newptr);
}

/**
 * _realloc2 - reallocates memory for char
 * @p: pointer to an array
 * Return: pointer to new memory
 */

char *_realloc2(char *p)
{
	int i = 0;
	char *newptr;

	if (p == NULL)
		return (NULL);

	while (*(p + i) != '\n')
		i++;

	newptr = malloc(sizeof(char) * i + 1);
	if (newptr == NULL)
		return (NULL);
	i = 0;
	while (*(p + i) != '\n')
	{
		*(newptr + i) = *(p + i);
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
 * free_token - frees the tokens in the t_array array
 * @t_array: array of tokens
 * Return: void
 */

void free_token(char **t_array)
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
 * @input: the original line entered by user
 * @newline: user input without newline char
 * @t_array: array of tokens
 * Return: void
 */
void free_all(char *input, char *newline, char **t_array)
{
	free_token(t_array);
	free(input);
	free(newline);
	free(t_array);
}
