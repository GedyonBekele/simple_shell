#include "shell.h"

/**
 * print_to_stdout - writes an array of characters to the standard output.
 * @string: pointer to the array of characters to print.
 * Return: the number of bytes written.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_to_stdout(char *string)
{
	return (write(STDOUT_FILENO, string, string_length(string)));
}

/**
 * print_to_stderr - writes an array of characters to the standard error.
 * @string: pointer to the array of characters to print.
 * Return: the number of bytes written.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_to_stderr(char *string)
{
	return (write(STDERR_FILENO, string, string_length(string)));
}

/**
 * print_error_message - prints an error message to the standard error.
 * @data: a pointer to the program's data structure.
 * @errorcode: error code to print.
 * Return: the number of bytes written.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_error_message(int errorcode, ProgramData *program_data)
{
	char counter_as_string[10] = {'\0'};

	num_to_string((long)program_data->exec_counter, counter_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		print_to_stderr(program_data->program_name);
		print_to_stderr(": ");
		print_to_stderr(counter_as_string);
		print_to_stderr(": ");
		print_to_stderr(program_data->tokens[0]);
		if (errorcode == 2)
			print_to_stderr(": Illegal number: ");
		else
			print_to_stderr(": can't cd to ");
		print_to_stderr(program_data->tokens[1]);
		print_to_stderr("\n");
	}
	else if (errorcode == 127)
	{
		print_to_stderr(program_data->program_name);
		print_to_stderr(": ");
		print_to_stderr(counter_as_string);
		print_to_stderr(": ");
		print_to_stderr(program_data->command_name);
		print_to_stderr(": not found\n");
	}
	else if (errorcode == 126)
	{
		print_to_stderr(program_data->program_name);
		print_to_stderr(": ");
		print_to_stderr(counter_as_string);
		print_to_stderr(": ");
		print_to_stderr(program_data->command_name);
		print_to_stderr(": Permission denied\n");
	}

	return (0);
}
