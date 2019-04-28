#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

void init(void);
void print_prompt(void);
void read_command(char**);

void pre_parse(char*);
void parse_command(char**);

pid_t exec_command(char*[100]);
