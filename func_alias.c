#include "shell.h"

/**
 * print_alias - add, remove, or show aliases
 * @program_data: struct for the program's data
 * @alias_name: name of the alias to be printed
 * Return: zero if success, or other number if it's declared in the arguments
 */
int print_alias(ProgramData *program_data, char *alias_name)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (program_data->alias_list)
	{
		alias_length = string_length(alias_name);
		for (i = 0; program_data->alias_list[i]; i++)
		{
			if (!alias_name || (string_compare(program_data->alias_list[i], alias_name,
							alias_length)
						&& program_data->alias_list[i][alias_length] == '='))
			{
				for (j = 0; program_data->alias_list[i][j]; j++)
				{
					buffer[j] = program_data->alias_list[i][j];
					if (program_data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				bufferAdd(buffer, "'");
				bufferAdd(buffer, program_data->alias_list[i] + j + 1);
				bufferAdd(buffer, "'\n");
				print_to_stdout(buffer);
			}
		}
	}
	return (0);
}

/**
 * get_alias - add, remove, or show aliases
 * @program_data: struct for the program's data
 * @alias_name: name of the requested alias.
 * Return: zero if success, or other number if it's declared in the arguments
 */
char *get_alias(ProgramData *program_data, char *alias_name)
{
	int i, alias_length;

	/* validate the arguments */
	if (alias_name == NULL || program_data->alias_list == NULL)
		return (NULL);
	alias_length = string_length(alias_name);
	for (i = 0; program_data->alias_list[i]; i++)
	{
		/* Iterates through the environ and check for coincidence of the varname */
		if (string_compare(alias_name, program_data->alias_list[i], alias_length) &&
				program_data->alias_list[i][alias_length] == '=')
		{
			/* returns the value of the key NAME= when found */
			return (program_data->alias_list[i] + alias_length + 1);
		}
	}
	/* returns NULL if not found */
	return (NULL);
}

/**
 * set_alias - add, or override alias
 * @alias_string: alias to be set in the form (name='value')
 * @program_data: struct for the program's data
 * Return: zero if success, or other number if it's declared in the arguments
 */
int set_alias(char *alias_string, ProgramData *program_data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;
	/* validate the arguments */
	if (alias_string == NULL || program_data->alias_list == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (i = 0; alias_string[i]; i++)
	{
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			/* search if the value of the alias is another alias */
			temp = get_alias(program_data, alias_string + i + 1);
			break;
		}
	}
	/* Iterates through the alias list and check for coincidence of the varname */
	for (j = 0; program_data->alias_list[j]; j++)
	{
		if (string_compare(buffer, program_data->alias_list[j], i) &&
				program_data->alias_list[j][i] == '=')
			/* if the alias already exists */
			free(program_data->alias_list[j]);
			break;
	}
	/* add the alias */
	if (temp)
	{
		/* if the alias already exists */
		bufferAdd(buffer, "=");
		bufferAdd(buffer, temp);
		program_data->alias_list[j] = string_duplicate(buffer);
	}
	else
		/* if the alias does not exist */
		program_data->alias_list[j] = string_duplicate(alias_string);
	return (0);
}
