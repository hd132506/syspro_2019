#include "yshell.h"
#define MAX_CMD_LEN 256

char *username, hostname[HOST_NAME_MAX], directory[PATH_MAX];


void print_prompt(void) {
   char *curdir = strrchr(directory, '/') + 1;
   printf("%s@%s:%s$ ", username, hostname, curdir);
}

void read_command(char **command) {
    *command = (char *)malloc(MAX_CMD_LEN*sizeof(char));
    
    if(fgets(*command, MAX_CMD_LEN, stdin) == NULL) {
        perror("yshell:Error occured while reading command\n");
        exit(1);
    }
}
