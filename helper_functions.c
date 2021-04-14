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
 * @concatenate: memory space to concatenate the strings
 * @s1: str 1
 * @s2: str 2
 * Return: pointer to concatenated memory space
 */

char *_concatenate(char *concatenate, char *s1, char *s2)
{
	int concatcounter = 0;
	int stringcounter = 0;

	while (*(s1 + stringcounter) != '\0')
	{
		*(concatenate + concatcounter) = *(s1 + stringcounter);
		concatcounter++;
		stringcounter++;
	}

	stringcounter = 0;
	while (*(s2 + stringcounter) != '\0')
	{
		*(concatenate + concatcounter) = *(s2 + stringcounter);
		concatcounter++;
		stringcounter++;
	}
	*(concatenate + concatcounter) = '\0';
	return (concatenate);
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
 * _strconcat - appends src to the dest string
 * @s1: string s1
 * @s2: string s1
 *
 * Return: concatenated string
 */
char *_strconcat(char *s1, char *s2)
{
	int lengths1 = 0;
	int lengths2 = 0;
	char *concatenate;

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

	lengths1 = _strlen(s1);
	lengths2 = _strlen(s2);

	concatenate = malloc(sizeof(char) * (lengths1 + lengths2 + 1));
	if (concatenate == NULL)
	{
		free(s1);
		free(s2);
		return (NULL);
	}

	return (_concatenate(concatenate, s1, s2));
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
