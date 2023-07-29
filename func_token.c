#include "shell.h"

/**
 * split_string - This function splits a string using a specified delimiter.
 * @data: A pointer to the program's data structure.
 * Return: An array of pointers to the different parts of the string.
 */
void split_string(ProgramData *program_data)
{
	char *delimiter = " \t";
	int i, j, token_count = 2, length;

	length = string_length(program_data->input_line);
	if (length)
	{
		if (program_data->input_line[length - 1] == '\n')
			program_data->input_line[length - 1] = '\0';
	}

	for (i = 0; program_data->input_line[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (program_data->input_line[i] == delimiter[j])
				token_count++;
		}
	}

	program_data->tokens = malloc(token_count * sizeof(char *));
	if (program_data->tokens == NULL)
	{
		perror(program_data->program_name);
		exit(errno);
	}

	i = 0;
	program_data->tokens[i] = string_duplicate(custom_strtok(program_data->input_line, delimiter));
	program_data->command_name = string_duplicate(program_data->tokens[0]);

	while (program_data->tokens[i++])
	{
		program_data->tokens[i] = string_duplicate(custom_strtok(NULL, delimiter));
	}
}

