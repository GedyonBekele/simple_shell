#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>

/*#define BUFFER_SIZE 1024*/

/* MACROS */
#include "func_macros.h"


/* STRUCTURES */

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct ProgramData 
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} ProgramData;

/** struct BuiltinCommand - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function 
 */
typedef struct BuiltinCommand 
{
	char *builtin;
	int (*function)(ProgramData *program_data);
} BuiltinCommand;

void inicialize_data(ProgramData program_data, int arc, char *argv[], char **env);

void sisifo(char *prompt, ProgramData *program_data);

void handle_ctrl_c(int opr UNUSED);



/* main.shell */
int main(int argc, char *argv[], char *env[]);
void handle_ctrl_c(int opr UNUSED);
void initialize_data(ProgramData *program_data, int argc, char *argv[], char **env);
void sisifo(char *prompt, ProgramData *program_data);



/*func_strtok*/
char *custom_strtok(char *str, char *delimiters);
char *func_strtok(char *input);

/*func_exec*/
int exec_command(ProgramData *program_data);

/* func_getline */
int func_getline(ProgramData *data);
int check_logical_operators(char *commands_array[], int i, char operators_array[]);


/* func_string.c */
int string_length(char *str);
char *string_duplicate(char *str);
int string_compare(char *str1, char *str2, int num);
char *string_concatenate(char *str1, char *str2);
void string_reverse(char *str);


/* func_path.c */
int count_occurrences(char *string, char *character);
char **tokenize_path(ProgramData *program_data);
int check_file(char *full_path);



/* func_num.c */
void num_to_string(long num, char *str, int base);
int string_to_int(char *str);
int count_occurrences(char *string, char *character);
int count_characters(char *string, char *character);


/* func_env_management.c */
int builtin_env(ProgramData *program_data);
int builtin_set_env(ProgramData *program_data);
int builtin_unset_env(ProgramData *program_data);

/* func_print.c */
int print_to_stdout(char *string);
int print_to_stderr(char *string);
int print_error_message(int errorcode, ProgramData);


/* func_free.c */
void free_all_data(ProgramData *program_data);
void free_array_of_pointers(char **array);
void free_recurrent_data(ProgramData *program_data);

/* func_token.c */
void split_string(ProgramData *program_data);


/* func_exp.c */
void expandVariables(ProgramData *program_data);
void expandAlias(ProgramData *program_data);
int bufferAdd(char *buffer, char *strToAdd);


/* func_alias.c */
int print_alias(ProgramData *program_data, char *alias_name);
char *get_alias(ProgramData *program_data, char *alias_name);
int set_alias(char *alias_string, ProgramData *program_data);

/* func_env_builtins.c */
int builtin_env(ProgramData *program_data);
int builtin_set_env(ProgramData *program_data);
int builtin_unset_env(ProgramData *program_data);

/* func_builtins_list.c */

int builtin_exit(ProgramData *program_data);
int builtin_cd(ProgramData *program_data);
int set_working_directory(ProgramData *program_data, char *new_dir);
int builtin_help(ProgramData *program_data);
int builtin_alias(ProgramData *program_data);

/* func_builtins_add.c */
int execute_builtin(ProgramData *program_data);

/* func_env_builtins.c */
int builtin_env(ProgramData *program_data);
int builtin_set_env(ProgramData *program_data);
int builtin_unset_env(ProgramData *program_data);

/* func_env_management.c */
int env_remove_key(char *key, ProgramData *program_data);
int setEnvironmentValue(char *key, char *value, ProgramData *program_data);
char *getEnvironmentValue(char *key, ProgramData *program_data);
void print_environ(ProgramData *program_data);




#endif













