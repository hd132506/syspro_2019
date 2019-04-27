#include "yshell.h"

extern int do_something;

void exec_program(char *[100]);

void exec_command(char *args[100], char *delimiter) {
    int i, start = 0;
    if(delimiter[0] == '\0') do_something = 0;

    for(i = 0; args[i]!=NULL; ++i) {
        /* Check and process delimiters */
        if(!strcmp(args[i], ";")) {
            args[i] = NULL;
            start = i+1;
            exec_program(args + start);
            wait(NULL);
        }
    }
    exec_program(args + start);
    wait(NULL);
}

void exec_program(char *args[100]) {
    pid_t pid = fork();
    if(pid == 0)
        if(execvp(args[0], args)==-1) {
            printf("yshell: Command not found \"%s\"\n", args[0]);
            exit(1);
        }
    else
        printf("yshell: Fork error\n");
}


