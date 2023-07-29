#include "shell.h"

/**
 * num_to_string - converts a number to a string.
 * @num: number to be converted into a string.
 * @str: buffer to save the number as a string.
 * @base: base to convert the number.
 *
 * Return: Nothing.
 */
void num_to_string(long num, char *str, int base)
{
	int index = 0, isNegative = 0;
	long quotient = num;
	char letters[] = "0123456789abcdef";

	if (quotient == 0)
		str[index++] = '0';

	if (str[0] == '-')
		isNegative = 1;

	while (quotient)
	{
		if (quotient < 0)
			str[index++] = letters[-(quotient % base)];
		else
			str[index++] = letters[quotient % base];
		quotient /= base;
	}
	if (isNegative)
		str[index++] = '-';
	str[index] = '\0';
	string_reverse(str);
}
/**
 * string_to_int - convert a string to an integer.
 *
 * @str: pointer to the source string.
 * Return: integer value of the string or 0 if conversion fails.
 */
int string_to_int(char *str)
{
	int sign = 1;
	unsigned int result = 0;
	/* 1- analyze the sign */
	while (!('0' <= *str && *str <= '9') && *str != '\0')
	{
		if (*str == '-')
			sign *= -1;
		if (*str == '+')
			sign *= +1;
		str++;
	}
	/* 2 - extract the number */
	while ('0' <= *str && *str <= '9' && *str != '\0')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * sign);
}

/**
 * count_occurrences - count the occurrences of a character in a string.
 *
 * @string: pointer to the source string.
 * @character: character to be counted.
 * Return: number of occurrences of the character in the string.
 */
int count_occurrences(char *string, char *character)
{
	int i = 0, counter = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			counter++;
	}
	return (counter);
}
