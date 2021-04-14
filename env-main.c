#include "shell.h"

/**
 * create_list - creates empty linked list the size of the path variable
 * @str: PATH variable name
 * Return: a pointer to the empty linked list
 */

linked_t *create_list(char *str)
{
	int i = 0;
	int nodes = 1;
	linked_t *node, *head, *tmp, *tail;

	tmp = malloc(sizeof(linked_t));
	if (tmp == NULL)
		return (NULL);
	head = tmp;

	tail = malloc(sizeof(linked_t));
	if (tail == NULL)
	{
		free(tmp);
		return (NULL);
	}
	tail->next = NULL;

	while (str[i] != '\0')
	{
		if (str[i] == ':')
			nodes++;
		i++;
	}

	while ((nodes - 2) > 0)
	{
		node = malloc(sizeof(linked_t));
		if (node == NULL)
		{
			free(tmp);
			free(tail);
			return (NULL);
		}
		tmp->next = node;
		tmp = tmp->next;
		nodes--;
	}
	tmp->next = tail;
	return (head);
}

/**
 * addto_list - add PATH variable contents to empty
 * @str: PATH variable name
 * @list: pointer to the empty linked list
 * Return: pointer to the resultant linked list
 */
linked_t *addto_list(char *str, linked_t *list)
{
	linked_t *ptr, *head;
	char *dirName;
	int i = 0, j = 0, stcnt = 0, dirLen = 0;

	if (str ==  NULL || list == NULL)
		return (NULL);
	head = list;
	ptr = head;
	while (ptr != NULL)
	{
		if (str[i] == ':' || str[i] == '\0')
		{
			if (str[i] != '\0')
				i++;
			dirName = malloc(sizeof(char) * dirLen + 2);
			if (dirName == NULL)
				return (NULL);
			while (str[stcnt] != ':' && str[stcnt] != '\0')
			{
				dirName[j] = str[stcnt];
				stcnt++;
				j++;
			}
			dirName[j++] = '/';
			dirName[j] = '\0';
			stcnt = i;
			j = 0;
			ptr->directory = dirName;
			ptr = ptr->next;
		}

		else
		{
			dirLen++;
			i++;
		}
	}
	return (head);
}

/**
 * _getenv - find env variable
 * @name: name of the environment variable
 * @env: the environment variable
 * Return: pointer to the environment variable
 */

char *_getenv(const char *name, char **env)
{
	int i, j = 0;

	if (name == NULL || env == NULL || *env == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		while (env[i][j] == name[j])
			j++;
		if (env[i][j] == '=')
		{
			j++;
			return (&(env[i][j]));
		}
		i++;
		j = 0;
	}
	write(STDOUT_FILENO, "Not found in environment", 24);
	return (NULL);
}

/**
 * _path - iterates through PATH variable and concatenates command into it
 * @str: PATH variables to concatenate
 * @env: the environment variable
 * Return: pointer to concatenated string
 */

char *_path(char *str, char **env)
{
	char *path, *abs_path;
	linked_t *list, *tmp;
	struct stat st;

	if (str == NULL || env == NULL || *env == NULL)
		return (NULL);
	path = _getenv("PATH", env);
	if (path == NULL)
	{
		write(STDERR_FILENO, "PATH not found", 14);
		_exit(0);
	}
	list = create_list(path);
	if (list == NULL)
	{
		write(STDERR_FILENO, "Errors PATH", 16);
		_exit(0);
	}
	list = addto_list(path, list);
	tmp = list;
	while (tmp != NULL)
	{
		if (path[0] == ':')
			abs_path = _strcat("./", str);
		else
			abs_path = _strcat(tmp->directory, str);
		if (abs_path == NULL)
			return (NULL);
		if (stat(abs_path, &st) == 0 && access(abs_path, X_OK) == 0)
		{
			free_list(list);
			return (abs_path);
		}
		tmp = tmp->next;
		free(abs_path);
	}
	free_list(list);
	return (NULL);
}
