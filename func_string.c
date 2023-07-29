#include "shell.h"

/**
 * string_length - Returns the length of a string.
 * @str: Pointer to the input string.
 * Return: Length of the string.
 */
int string_length(char *str)
{
	int length = 0;

	if (str == NULL)
		return (0);

	while (str[length++] != '\0')
	{
	}
	return (--length);
}

/**
 * string_duplicate - Creates a duplicate of a string.
 * @str: String to be copied.
 * Return: Pointer to the newly duplicated string.
 */
char *string_duplicate(char *str)
{
	char *result;
	int length, i;

	if (str == NULL)
		return (NULL);

	length = string_length(str) + 1;
	result = malloc(sizeof(char) * length);
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < length; i++)
	{
		result[i] = str[i];
	}
	return (result);
}

/**
 * string_compare - Compares two strings up to a specified no. of characters.
 * @str1: First string, or the shorter one.
 * @str2: Second string, or the longer one.
 * @num: Number of characters to be compared, 0 for an infinite comparison.
 * Return: 1 if the strings are equal, 0 if they are different.
 */
int string_compare(char *str1, char *str2, int num)
{
	int iterator;

	if (str1 == NULL && str2 == NULL)
		return (1);
	if (str1 == NULL || str2 == NULL)
		return (0);
	if (num == 0) /* Infinite comparison */
	{
		if (string_length(str1) != string_length(str2))
			return (0);
		for (iterator = 0; str1[iterator]; iterator++)
		{
			if (str1[iterator] != str2[iterator])
				return (0);
		}
		return (1);
	}
	else /* Comparison with a specified number of characters */
	{
		for (iterator = 0; iterator < num; iterator++)
		{
			if (str1[iterator] != str2[iterator])
				return (0);
		}
		return (1);
	}
}

/**
 * string_concatenate - Concatenates two strings.
 * @str1: First string to be concatenated.
 * @str2: Second string to be concatenated.
 * Return: Pointer to the newly concatenated string.
 */
char *string_concatenate(char *str1, char *str2)
{
	char *result;
	int len1 = 0, len2 = 0;

	if (str1 == NULL)
		str1 = "";
	len1 = string_length(str1);
	if (str2 == NULL)
		str2 = "";
	len2 = string_length(str2);
	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* Copy the content of str1 */
	for (len1 = 0; str1[len1] != '\0'; len1++)
		result[len1] = str1[len1];
	free(str1);

	/* Copy the content of str2 */
	for (len2 = 0; str2[len2] != '\0'; len2++)
	{
		result[len1] = str2[len2];
		len1++;
	}
	result[len1] = '\0';
	return (result);
}
/**
 * string_reverse - Reverses a string in place.
 * @str: Pointer to the input string.
 * Return: void.
 */
void string_reverse(char *str)
{
	int i = 0, length = string_length(str) - 1;
	char temp;

	while (i < length)
	{
		temp = str[i];
		str[i++] = str[length];
		str[length--] = temp;
	}
}
