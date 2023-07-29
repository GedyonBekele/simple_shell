#include "shell.h"

/**
 * builtin_exit - handles the 'exit' command
 * @program_data: struct for the program's data
 * Return: Returns the exit code for the shell.
 */
int builtin_exit(ProgramData *program_data)
{
	int i;

	if (program_data->tokens[1] != NULL)
	{
		/* Check if the argument for exit is a number */
		for (i = 0; program_data->tokens[1][i]; i++)
		{
			if ((program_data->tokens[1][i] < '0' ||
						program_data->tokens[1][i] > '9') &&
					program_data->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		}
		errno = string_to_int(program_data->tokens[1]);
	}

	free_all_data(program_data);
	exit(errno);
}

/**
 * builtin_cd - handles the 'cd' command to change the current directory
 * @program_data: struct for the program's data
 * Return: Returns zero if successful, or other number if there are arguments.
 */
int builtin_cd(ProgramData *program_data)
{
	char *home_dir = getEnvironmentValue("HOME", program_data);
	char *old_dir = NULL;
	char old_dir_path[128] = {0};
	int error_code = 0;

	if (program_data->tokens[1])
	{
		if (string_compare(program_data->tokens[1], "-", 0))
		{
			old_dir = getEnvironmentValue("OLDPWD", program_data);
			if (old_dir)
				error_code = set_working_directory(program_data, old_dir);
			print_to_stdout(getEnvironmentValue("PWD", program_data));
			return (error_code);
		}
		else
		{
			return (set_working_directory(program_data, program_data->tokens[1]));
		}
	}
	else
	{
		if (!home_dir)
			home_dir = getcwd(old_dir_path, 128);

		return (set_working_directory(program_data, home_dir));
	}

	return (0);
}

/**
 * set_working_directory - sets the working directory
 * @program_data: struct for the program's data
 * @new_dir: path to be set as the working directory
 * Return: Returns zero if successful, or other number if there is an error.
 */
int set_working_directory(ProgramData *program_data, char *new_dir)
{
	char old_dir_path[128] = {0};
	int err_code = 0;

	getcwd(old_dir_path, 128);

	if (!string_compare(old_dir_path, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		setEnvironmentValue("PWD", new_dir, program_data);
	}
	setEnvironmentValue("OLDPWD", old_dir_path, program_data);
	return (0);
}

/**
 * builtin_help - displays help messages for builtins
 * @program_data: struct for the program's data
 * Return: Returns zero if successful, or other number if there are arguments.
 */
int builtin_help(ProgramData *program_data)
{
	int i, length = 0;
	char *help_messages[6] = {NULL};

	help_messages[0] = HELP_MSG;

	/* Validate arguments */
	if (program_data->tokens[1] == NULL)
	{
		print_to_stdout(help_messages[0] + 6);
		return (1);
	}

	if (program_data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(program_data->command_name);
		return (5);
	}

	help_messages[1] = HELP_EXIT_MSG;
	help_messages[2] = HELP_ENV_MSG;
	help_messages[3] = HELP_SETENV_MSG;
	help_messages[4] = HELP_UNSETENV_MSG;
	help_messages[5] = HELP_CD_MSG;

	for (i = 0; help_messages[i]; i++)
	{
		/* Print the help message if there is a match */
		length = string_length(program_data->tokens[1]);
		if (string_compare(program_data->tokens[1], help_messages[i], length))
		{
			print_to_stdout(help_messages[i] + length + 1);
			return (1);
		}
	}
	/* If there is no match, print an error and return -1 */
	errno = EINVAL;
	perror(program_data->command_name);
	return (0);
}

/**
 * builtin_alias - handles the 'alias' command to add, remove, or show aliases
 * @program_data: struct for the program's data
 * Return: Returns zero if successful, or other number if there are arguments.
 */
int builtin_alias(ProgramData *program_data)
{
	int i = 0;

	/* If there are no arguments, print all aliases */
	if (program_data->tokens[1] == NULL)
		return (print_alias(program_data, NULL));

	while (program_data->tokens[++i])
	{
		/* If there are arguments, set or print each alias */
		if (count_characters(program_data->tokens[i], "="))
			set_alias(program_data->tokens[i], program_data);
		else
			print_alias(program_data, program_data->tokens[i]);
	}

	return (0);
}
