#include "shell.h"

/**
 * exec_command - execute a command with entire path variable.
 * @program_data: pointer to program's data
 *
 * Return: 0 (success) otherwise -1
 */
int exec_command(ProgramData *program_data)
{
	int calc_val = 0;
	int status;
	pid_t pid;

	/* check program for built-ins */
	if (calc_val != -1)
	{/* built-ins found */
		return (calc_val);
	}

	/* check for program in file system */
	calc_val = execute.builtin(program_data);
	if (calc_val)
	{/* program not found */
		return (calc_val);
	}
	else
	{/* if program found */
		pid = fork();/* child process create */
		if (pid == -1)
		{/*if the fork failed */
			perror(program_data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{/* I am the child process, I execute the program */
			calc_val = execve(program_data->tokens[0],
					program_data->tokens, program_data->env);
			if (calc_val == -1)/* if error when execve */
				perror(program_data->command_name), exit(EXIT_FAILURE);
		}
		else/* parent, wait */
			wait(&status);
		if ((WIFEXITED)(status))
				errno = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			errno = 128 + WTERMSIG(status);
	}
	return (0);
}
