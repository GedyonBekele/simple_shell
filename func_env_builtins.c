#include "shell.h"

/**
 * builtin_env - shows the environment where the shell runs
 * @program_data: struct for the program's data
 * Return: zero if success, or other number if it's declared in the arguments
 */
int builtin_env(ProgramData *program_data)
{
	int i;
	char var_name[50] = {'\0'};
	char *var_copy = NULL;

	/* if no arguments */
	if (program_data->tokens[1] == NULL)
		print_environ(program_data);
	else
	{
		for (i = 0; program_data->tokens[1][i]; i++)
		{
			/* checks if there is a char '=' */
			if (program_data->tokens[1][i] == '=')
			{
				/* if a variable with the same name, temporarily change its value */
				var_copy = string_duplicate(getEnvironmentValue(var_name, program_data));
				if (var_copy != NULL)
					setEnvironmentValue(var_name, program_data->tokens[1] + i + 1, program_data);

				/* print the environment */
				print_environ(program_data);
				if (getEnvironmentValue(var_name, program_data) == NULL)
					/* print the variable if it does not exist in the environment */
					print_to_stdout(program_data->tokens[1]);
				string_reverse(str);
					print_to_stdout("\n");
				else
					/* returns the old value of the variable */
					setEnvironmentValue(var_name, var_copy, program_data);
					free(var_copy);
				return (0);
			}
			var_name[i] = program_data->tokens[1][i];
		}
		errno = 2;
		perror(program_data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - ...
 * @program_data: struct for the program's data
 * Return: zero if success, or other number if it's declared in the arguments
 */
int builtin_set_env(ProgramData *program_data)
{
	/* validate args */
	if (program_data->tokens[1] == NULL || program_data->tokens[2] == NULL)
		return (0);
	if (program_data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(program_data->command_name);
		return (5);
	}

	setEnvironmentValue(program_data->tokens[1], program_data->tokens[2], program_data);

	return (0);
}

/**
 * builtin_unset_env - ...
 * @program_data: struct for the program's data
 * Return: ...
 */
int builtin_unset_env(ProgramData *program_data)
{
	/* validate args */
	if (program_data->tokens[1] == NULL)
		return (0);
	if (program_data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(program_data->command_name);
		return (5);
	}
	env_remove_key(program_data->tokens[1], program_data);

	return (0);
}
