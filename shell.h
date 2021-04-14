#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <limits.h>

/**
 * struct path_s - linked list structure for PATH variable
 * @directory: directory to lookup
 * @next: pointer to the next node
 */

typedef struct path_s
{
	char *directory;
	struct path_s *next;
} linked_t;

int _putchar(char c);
void shellPrompt(void);
char **tokenize(char *line);

/* path functions */
linked_t *create_list(char *str);
linked_t *addto_list(char *str, linked_t *list);
char *_getenv(const char *name, char **env);
char *_path(char *str, char **env);

/* error_handling */
void no_ferror(char **argv, char **arr, int cmd_count, char *line, char *nline);

/* str helper functions */
char *_strdup(char *str);
int _strlen(char *s);
char *_strcat(char *s1, char *s2);
int _strcmp(char *s1, char *s2);
char *_concatenate(char *concatenated, char *s1, char *s2);

/* builtin functions */
int exit_handler(char **arr, char *line, char *newline, int cmd_count);
int cd_handler(char **arr, char **env);
int env_handler(char **env);
int execute(char **arr, char **env, char **av, char *line, char *nline, int cmd_count);
int checkBuiltin(char **arr, char **env, char *line, char *nline, int cmd_count);

/* strint functions */
int _atoi(char *s);
int tens_place(int i, char *s);
char *print_int(int num);

/* signal handler */
void ctrlc_handler(int signum);
int ctrld_handler(char *line);

/* memory handling */
char *_realloc(char *p);
void free_list(linked_t *head);
void free_token(char **t_array);
void free_all(char *line, char *newline, char **t_array);

#endif
