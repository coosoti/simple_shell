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

/* exec.c */
int execute_cmd(char **ar, char **env, char **av, char *line, char *nline,
		int cmd_count);

/* prompt.c */
void shellPrompt(void);

/* shell.c */
char **tokenize(char *line);

/* path functions */
linked_t *create_linkedt(char *str);
linked_t *addnodes_list(char *str, linked_t *list);
char *_getenv(const char *name, char **env);
char *path_handler(char *str, char **env);


/* error_handling */
void error_handler(char **argv, char **ar, int cmdcount_int, char *line,
		   char *nline);

/* str helper functions */
int _strlen(char *buf);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_concatenate(char *concatenate, char *s1, char *s2);
char *_strconcat(char *s1, char *s2);

/* builtin functions */
int exit_handler(char **array, char *line, char *newline, int cmd_count);
int cd_handler(char **array, char **env);
int env_handler(char **env);
int checkBuiltins(char **ar, char **env, char *line, char *newline,
		  int cmd_count);


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
void free_tokens(char **t_array);
void free_all(char *line, char *newline, char **t_array);

#endif
