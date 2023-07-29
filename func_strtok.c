#include "shell.h"

/**
 * custom_strtok - tokenizes a string using specified delimiters.
 * @str: Pointer to the input string to be tokenized.
 * @delimiters: Pointer to the characters used as delimiters.
 * Return: A pointer to the created token.
 */
char *custom_strtok(char *str, char *delimiters)
{
	int i;
	static char *current_str;
	char *token_start;

	if (str != NULL)
		current_str = str;

	for (; *current_str != '\0'; current_str++)
	{
		for (i = 0; delimiters[i] != '\0'; i++)
		{
			if (*current_str == delimiters[i])
				break;
		}

		if (delimiters[i] == '\0')
			break;
	}

	token_start = current_str;

	if (*token_start == '\0')
		return (NULL);

	for (; *current_str != '\0'; current_str++)
	{
		for (i = 0; delimiters[i] != '\0'; i++)
		{
			if (*current_str == delimiters[i])
			{
				*current_str = '\0';
				current_str++;
				return (token_start);
			}
		}
	}

	return (token_start);
}
