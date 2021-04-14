#include "shell.h"

/**
 *_strdup - returns pointer to allocated space containing copy of string
 *@str: string that will be copied into the space
 *
 *Return: pointer to allocated space
 */
char *_strdup(char *str)
{
	int i = 0;
	int length = 0;
	char *string;

	if (str == NULL)
		return (NULL);

	while (*(str + i) != '\0')
	{
		length++;
		i++;
	}

	i = 0;
	string = malloc(sizeof(char) * length + 1);

	if (string == NULL)
		return (NULL);

	while (*(str + i) != '\0')
	{
		*(string + i) = *(str + i);
		i++;
	}
	*(string + i) = '\0';
	return (string);
}

/**
 * _concatenate - concatenates two strings
 * @concatenated: memory space to concatenate the strings
 * @s1: str 1
 * @s2: str 2
 * Return: pointer to concatenated memory space
 */
char *_concatenate(char *concatenated, char *s1, char *s2)
{
	int concat_counter, str_counter = 0;

	while (*(s1 + str_counter) != '\0')
	{
		*(concatenated + concat_counter) = *(s1 + str_counter);
		concat_counter++;
		str_counter++;
	}

	str_counter = 0;
	while (*(s2 + str_counter) != '\0')
	{
		*(concatenated + concat_counter) = *(s2 + str_counter);
		concat_counter++;
		str_counter++;
	}
	*(concatenated + concat_counter) = '\0';
	return (concatenated);
}

/**
 * _strlen - func to return the length of a string
 *
 * @s: str param
 *
 * Return: len of the string
 */

int _strlen(char *s)
{
	int len = 0;
	int i = 0;

	if (s == NULL)
		return (-1);

	while (s[i] != '\0')
	{
		len = len + 1;
		i++;
	}

	return (len);

}

/**
 * _strcat - appends src to the dest string
 * @dest: string to append by src
 * @src: string to append to dest
 *
 * Return: address of dest
 */

char *_strcat(char *s1, char *s2)
{
	int len1, len2 = 0;
	char *concatenated;

	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char));
		if (s1 == NULL)
			return (NULL);
		*s1 = '\0';
	}

	if (s2 == NULL)
	{
		s2 = malloc(sizeof(char));
		if (s2 == NULL)
			return (NULL);
		*s2 = '\0';
	}

	len1 = _strlen(s1);
	len2 = _strlen(s2);

	concatenated = malloc(sizeof(char) * (len1 + len2 + 1));

	if (concatenated == NULL)
	{
		free(s1);
		free(s2);
		return (NULL);
	}

	return (_concatenate(concatenated, s1, s2));
}

/**
 * _strcmp - Compares pointers to two strings.
 * @s1: A pointer to the first string to be compared.
 * @s2: A pointer to the second string to be compared.
 *
 * Return: If str1 < str2, the negative difference of the first unmatched
 *characters.
 * If str1 == str2, 0.
 * If str1 > str2, the positive difference of the first unmatched characters.
 */

int _strcmp(char *s1, char *s2)
{
	while ((*s1 == *s2) && *s1 != '\0' && *s2 != '\0')
	{
		s1++;
		s2++;
	}

	if ((*s1 == '\0') && (*s2 == '\0'))
		return (0);
	else if (*s1 > *s2)
		return ((int)(*s1 - *s2));
	else
		return ((int)(*s1 - *s2));
}
