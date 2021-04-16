#include "shell.h"

/**
 * create_linkedt - creates empty linked list the size of the path variable
 * @str: PATH variable name
 * Return: a pointer to the empty linked list
 */
linked_t *create_linkedt(char *str)
{
	int i = 0;
	int nodes = 1;
	linked_t *node, *head, *tmp, *end;

	tmp = malloc(sizeof(linked_t));
	if (tmp == NULL)
		return (NULL);
	head = tmp;

	end = malloc(sizeof(linked_t));
	if (end == NULL)
	{
		free(tmp);
		return (NULL);
	}
	end->next = NULL;

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
			free(end);
			return (NULL);
		}
		tmp->next = node;
		tmp = tmp->next;
		nodes--;
	}
	tmp->next = end;
	return (head);
}

/**
 * addnodes_list - add PATH variable contents to empty
 * @str: PATH variable name
 * @list: pointer to the empty linked list
 * Return: pointer to the resultant linked list
 */

linked_t *addnodes_list(char *str, linked_t *list)
{
	linked_t *ptr, *head;
	char *dir;
	int i = 0, j = 0, stcnt = 0, dirlen = 0;

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
			dir = malloc(sizeof(char) * dirlen + 2);
			if (dir == NULL)
				return (NULL);
			while (str[stcnt] != ':' && str[stcnt] != '\0')
			{
				dir[j] = str[stcnt];
				stcnt++;
				j++;
			}
			dir[j++] = '/';
			dir[j] = '\0';
			stcnt = i;
			j = 0;
			ptr->directory = dir;
			ptr = ptr->next;
		}

		else
		{
			dirlen++;
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
	int i = 0;
	int j = 0;

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
 * path_handler - iterates through PATH variable and
 * concatenates command
 * @str: PATH variables to concatenate
 * @env: the environment variable
 * Return: pointer to concatenated string
 */

char *path_handler(char *str, char **env)
{
	char *path, *concat;
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
	list = create_linkedt(path);
	if (list == NULL)
	{
		write(STDERR_FILENO, "Issues with PATH", 16);
		_exit(0);
	}
	list = addnodes_list(path, list);
	tmp = list;
	while (tmp != NULL)
	{
		if (path[0] == ':')
			concat = _strconcat("./", str);
		else
			concat = _strconcat(tmp->directory, str);
		if (concat == NULL)
			return (NULL);
		if (stat(concat, &st) == 0 && access(concat, X_OK) == 0)
		{
			free_list(list);
			return (concat);
		}
		tmp = tmp->next;
		free(concat);
	}
	free_list(list);
	return (NULL);
}
