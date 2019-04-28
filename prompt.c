#include "yshell.h"
#include <time.h>
#define MAX_CMD_LEN 256

char *username, hostname[HOST_NAME_MAX], directory[PATH_MAX];
int n_commands;

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

    /* Record command into yhistory with the time it's been entered */
    int history_fd = open(".yhistory", O_WRONLY | O_APPEND);
    time_t now; time(&now);
    char *str_now = ctime(&now), *buffer;
    int time_len = strlen(str_now), cmd_len = strlen(*command);
    str_now[--time_len] = '\0'; /* delete new line */
    buffer = malloc(sizeof(char)*time_len*cmd_len + 10);
    sprintf(buffer, "(%d)%s: %s", ++n_commands, str_now, *command);
    write(history_fd, buffer, strlen(buffer));

    close(history_fd);
}
