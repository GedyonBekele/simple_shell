#include "shell.h"

/**
 * expandVariables - Expand variables in the input line.
 * @programData: A pointer to a struct containing the program's data.
 *
 * Return: Nothing, but sets errno.
 */
void expandVariables(ProgramData *program_data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (program_data->input_line == NULL)
		return;
	bufferAdd(line, program_data->input_line);
	for (i = 0; line[i]; i++)
	{
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
			line[i] = '\0';
			longToString(errno, expansion, 10);
			bufferAdd(line, expansion);
			bufferAdd(line, program_data->input_line + i + 2);
		else if (line[i] == '$' && line[i + 1] == '$')
		line[i] = '\0';
			longToString(getpid(), expansion, 10);
			bufferAdd(line, expansion);
			bufferAdd(line, program_data->input_line + i + 2);
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			temp = getEnvironmentValue(expansion, program_data);
			line[i] = '\0';
			expansion[0] = '\0';
			bufferAdd(expansion, line + i + j);
			temp ? bufferAdd(line, temp) : 1;
			bufferAdd(line, expansion);
		}
	}
	if (!string_compare(program_data->input_line, line, 0))
		free(program_data->input_line);
	program_data->input_line = string_duplicate(line);
}


/**
 * expandAlias - Expand aliases in the input line.
 * @programData: A pointer to a struct containing the program's data.
 *
 * Return: Nothing, but sets errno.
 */
void expandAlias(ProgramData *program_data)
{
	int i, j, wasExpanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (program_data->input_line == NULL)
		return;
	bufferAdd(line, program_data->input_line);
	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';
		temp = getAliasValue(program_data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			bufferAdd(expansion, line + i + j);
			line[i] = '\0';
			bufferAdd(line, temp);
			line[string_length(line)] = '\0';
			bufferAdd(line, expansion);
			wasExpanded = 1;
		}
		break;
	}
	if (wasExpanded)
	{
		free(program_data->input_line);
		program_data->input_line = string_duplicate(line);
	}
}
/**
 * bufferAdd - Append a string at the end of the buffer.
 * @buffer: The buffer to be filled.
 * @strToAdd: The string to be copied into the buffer.
 *
 * Return: Nothing, but sets errno.
 */
int bufferAdd(char *buffer, char *strToAdd)
{
	int length, i;

	length = string_length(buffer);
	for (i = 0; strToAdd[i]; i++)
	{
		buffer[length + i] = strToAdd[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}
