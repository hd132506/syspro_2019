#include "yshell.h"

void exec_command(char *args[100]) {
    pid_t pid = fork();

    if(pid == 0)
        if(execvp(args[0], args)==-1) 
             printf("yshell: Command not found \"%s\"\n", args[0]);
    else
        printf("yshell: Fork error\n");
    wait(NULL);
}
