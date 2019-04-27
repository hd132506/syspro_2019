#include "yshell.h"
#define MAX_CMD_LEN 256

void print_prompt(void) {
   printf("%s $ ", hostname);
}

void read_command(char **command) {
    *command = (char *)malloc(MAX_CMD_LEN*sizeof(char));
    
    if(fgets(*command, MAX_CMD_LEN, stdin) == NULL) {
        perror("yshell:Error occured while reading command\n");
        exit(1);
    }
}
