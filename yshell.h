#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/types.h>


char *username;
char hostname[HOST_NAME_MAX];

void init(void);
void print_prompt(void);
void read_command(char**);

void pre_parse(char*);
void parse_command(char*(*)[100], char*);

void exec_command(char*[100]);
