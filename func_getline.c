#include "shell.h"

/**
 * _read_input_line - Read one line of input from the prompt.
 * @data: Pointer to the program's data.
 *
 * Return: Number of characters read.
 */
int func_getline(ProgramData *program_data)
{
	char buffer[BUFFER_SIZE] = {'\0'};
	static char *commands_array[10] = {NULL};
	static char operators_array[10] = {'\0'};
	ssize_t bytes_read;
	int i = 0;

	/* Check if there are no more commands in the array */
	/* and check the logical operators */
	if (!commands_array[0] || (operators_array[0] == '&' && errno != 0) ||
			(operators_array[0] == '|' && errno == 0))
	{
		/* Free the memory allocated in the array if it exists */
		for (i = 0; commands_array[i]; i++)
		{
			free(commands_array[i]);
			commands_array[i] = NULL;
		}
		/* Read from the file descriptor into buffer */
		bytes_read = read(program_data->file_descriptor, &buffer, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);
		/* Split lines for '\n' or ';' */
		i = 0;
		do {
			commands_array[i] = string_duplicate(custom_strtok(i ? NULL : buffer, "\n;"));
			/* Check and split for '&&' and '||' operators */
		       i = check_logical_operators(commands_array, i, operators_array);
		} while (commands_array[i++]);
	}
	/*obtain the next command (command 0) and remove it from the array */
	program_data->input_line = commands_array[0];
	for (i = 0; commands_array[i]; i++)
	{
		commands_array[i] = commands_array[i + 1];
		operators_array[i] = operators_array[i + 1];
	}
	return (string_length(program_data->input_line));
}
/**
 * check_logical_operators - Check and split for '&&' and '||' operators.
 * @commands_array: Array of the commands.
 * @i: Index in the commands_array to be checked.
 * @operators_array: Array of the logical operators for each previous command.
 *
 * Return: Index of the last command in the commands_array.
 */
int check_logical_operators(char *commands_array[],
		int i, char operators_array[])
{
	char *temp = NULL;
	int j;
	/* Check for the '&' char in the command line */
	for (j = 0; commands_array[i] != NULL && commands_array[i][j]; j++)
	{
		if (commands_array[i][j] == '&' && commands_array[i][j + 1] == '&')
		{
			/* Split the line when '&&' was found */
			temp = commands_array[i];
			commands_array[i][j] = '\0';
			commands_array[i] = string_duplicate(commands_array[i]);
			commands_array[i + 1] = string_duplicate(temp + j + 2);
			i++;
			operators_array[i] = '&';
			free(temp);
			j = 0;
		}
		if (commands_array[i][j] == '|' && commands_array[i][j + 1] == '|')
		{
			/* Split the line when '||' was found */
			temp = commands_array[i];
			commands_array[i][j] = '\0';
			commands_array[i] = string_duplicate(commands_array[i]);
			commands_array[i + 1] = string_duplicate(temp + j + 2);
			i++;
			i;
			operators_array[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}
