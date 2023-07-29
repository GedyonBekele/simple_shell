#include "shell.h"

/**
 * free_recurrent_data - free the fields needed for each loop iteration.
 * @data: pointer to the program's data structure.
 * Return: Nothing.
 */
void free_recurrent_data(ProgramData *program_data)
{
	if (program_data->tokens)
		free_array_of_pointers(program_data->tokens);
	if (program_data->input_line)
		free(program_data->input_line);
	if (program_data->command_name)
		free(program_data->command_name);

	program_data->input_line = NULL;
	program_data->command_name = NULL;
	program_data->tokens = NULL;
}

/**
 * free_all_data - free all fields of the data structure.
 * @data: pointer to the program's data structure.
 * Return: Nothing.
 */
void free_all_data(ProgramData *program_data)
{
	if (program_data->file_descriptor != 0)
	{
		if (close(program_data->file_descriptor) == -1)
			perror(ProgramData->program_name);
	}

	free_recurrent_data(program_data);
	free_array_of_pointers(program_data->env);
	free_array_of_pointers(program_data->alias_list);
}

/**
 * free_array_of_pointers - frees each pointer in an array and
 * the array itself.
 * @array: array of pointers to be freed.
 * Return: Nothing.
 */
void free_array_of_pointers(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}
