#include "shell.h"

/**
 * find_program - Find a program in the PATH environment variable.
 * @data: A pointer to the program's data.
 * Return: 0 success, or an error code otherwise.
 */
int find_program(ProgramData *program_data)
{
	int i = 0, ret_code = 0;
	char **directories;

	if (!program_data->command_name)
		return (2);

	/** Check if it's a full path or an executable in the current directory */
	if (program_data->command_name[0] == '/' || program_data->command_name[0] == '.')
		return (check_file(program_data->command_name));
	free(program_data->tokens[0]);
	program_data->tokens[0] = string_concatenate(string_duplicate("/"), program_data->command_name);
	if (!program_data->tokens[0])
		return (2);

	/* Search for the command in the directories listed in PATH */
	directories = tokenize_path(program_data);
	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}

	for (i = 0; directories[i]; i++)
	{
		directories[i] = string_concatenate(directories[i], program_data->tokens[0]);
		ret_code = check_file(directories[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			/* The file was found, is not a directory, and has execute permissions */
			errno = 0;
			free(program_data->tokens[0]);
			program_data->tokens[0] = string_duplicate(directories[i]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}
	free(program_data->tokens[0]);
	program_data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

/**
 * tokenize_path - Tokenize the PATH environment variable to
 * extract directories.
 * @data: A pointer to the program's data.
 * Return: Array of path directories.
 */
char **tokenize_path(ProgramData *program_data)
{
	int i = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	/* Get the value of the PATH environment variable */
	PATH = getEnvironmentValue("PATH", program_data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		/* PATH not found or empty */
		return (NULL);
	}

	PATH = string_duplicate(PATH);
	/* Find the number of directories in the PATH */
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			counter_directories++;
	}

	/* Reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * counter_directories);
	/* Tokenize and duplicate each directory in the PATH */
	i = 0;
	tokens[i] = string_duplicate(custom_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = string_duplicate(custom_strtok(NULL, ":"));
	}
	free(PATH);
	PATH = NULL;
	return (tokens);
}

/**
 * check_file - Check if a file exists, is not a directory,
 * and has execution permissions.
 * @full_path: Pointer to the full file name.
 * Return: 0 on success (file found and executable),
 * * or an error code if it doesn't exist or lacks permissions.
 */
int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) || access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/* File does not exist */
	errno = 127;
	return (127);
}
