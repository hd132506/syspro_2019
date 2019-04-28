#include "yshell.h"
#include <pwd.h>

extern int do_something;
extern char directory[PATH_MAX];

pid_t exec_command(char *args[100]) {
    if(!strcmp(args[0], "cd")) {
        if(chdir(args[1]) == -1)
            printf("yshell: invalid directory\n");
        getcwd(directory, sizeof(directory));
        return getpid();
    }

    pid_t pid = fork();
    if(pid == 0)
        if(execvp(args[0], args)==-1) {
            printf("yshell: Command not found \"%s\"\n", args[0]);
            exit(1);
        }
    else
        printf("yshell: Fork error\n");
    return pid;
}


