#include "shell.h"



int main(int argc, char *argv[], char *env[])
{
	ProgramData data_struct = {NULL}, *program_data = &data_struct;
	char *prompt = "";

	initialize_data(program_data, argc, argv, env);
	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{ /* We are in the terminal, interactive mode */
		errno = 2; /* ?? */
		prompt = PROMPT_MSG;
	}
	errno = 0;
	sisifo(prompt, program_data);
	return (0);
}
/**
 * handle_ctrl_c - prompt to new line
 *
 * @UNUSED: option 
 * Return: NULL
 */
void handle_ctrl_c(int opr UNUSED)
{
	print_to_stdout("\n");
	print_to_stdout(PROMPT_MSG);
}
void initialize_data(ProgramData *program_data, int argc, char *argv[], char **env)
{
	int i = 0;

	program_data->program_name = argv[0];
	program_data->input_line = NULL;
	program_data->command_name = NULL;
	program_data->exec_counter = 0;
	/* define the file descriptor to be readed */
	if (argc == 1)
		program_data->file_descriptor = STDIN_FILENO;
	else
	{
		program_data->file_descriptor = open(argv[1], O_RDONLY);
		if (program_data->file_descriptor == -1)
		{
			print_to_stderr(program_data->program_name);
			print_to_stderr(": 0: Can't open ");
			print_to_stderr(argv[1]);
			print_to_stderr("\n");
			exit(127);
		}
	}
	program_data->tokens = NULL;
	program_data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			program_data->env[i] = string_duplicate(env[i]);
		}
	}
	program_data->env[i] = NULL;
	env = program_data->env;
	program_data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		program_data->alias_list[i] = NULL;
	}
}


void sisifo(char *prompt, ProgramData *program_data)
{
	int error_code = 0, string_len = 0;

	while (++(program_data->exec_counter))
	{
		print_to_stdout(prompt);
		error_code = string_len = func_getline(program_data);
		if (error_code == EOF)
		{
			free_all_data(program_data);
			exit(errno); /* if EOF is the first Char of string, exit */
		}
		if (string_len >= 1)
		{
			expandAlias(program_data);
			expandVariables(program_data);
			tokenize_path(program_data);
			if (program_data->tokens[0])
			{ /* if a text is given to prompt, execute */
				error_code = execute(program_data);
				if (error_code != 0)
					print_error_message(error_code, program_data);
			}
			free_recurrent_data(program_data);
		}
	}
}
