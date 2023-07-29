#include "shell.h"
/**
 * execute_builtin - searches for a match and
 * executes the associated builtin command
 * @program_data: struct for the program's data
 * Return: Returns the return value of the executed
 * function if there is a match,
 * otherwise returns -1.
 **/
int execute_builtin(ProgramData *program_data)
{
	int iterator;
	BuiltinCommand builtin_commands[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

	/* Walk through the builtin_commands array */
	for (iterator = 0; builtin_commands[iterator].builtin != NULL; iterator++)
	{
		/* If there is a match between the given command and a builtin, */
		if (string_compare(builtin_commands[iterator].builtin,
					program_data->command_name, 0))
		{
			/* Execute the function and return the return value of the function */
			return (builtin_commands[iterator].function(program_data));
		}
		/* If there is no match, continue to the next iteration */
	}
	return (0);
}
