#include "yshell.h"
#include <pwd.h>
#include <errno.h>

extern int do_something;
extern char directory[PATH_MAX];

extern void refresh_history();

pid_t exec_command(char *args[100]) {
    if(!strcmp(args[0], "cd")) {
        if(chdir(args[1] == NULL ? "/home" : args[1]) == -1)
            printf("yshell: invalid directory\n");
        getcwd(directory, sizeof(directory));
        return getpid();
    }
    else if(!strcmp(args[0], "history")) { 
        char buffer[100] = {};
        int ret, history_fd = open(".yhistory", O_RDONLY);
        if(args[1] == NULL) {
            while((ret = read(history_fd, buffer, 100)) != 0) {
                if(ret == -1) {
                    if(errno == EINTR) continue; /* Retry when trivial error */
                    perror("History read error\n");
                    break;
                }
                printf("%s", buffer); memset(buffer, 0, sizeof(buffer));
            }
        }
        if(args[1] != NULL && !strcmp(args[1], "refresh")) {  
            refresh_history();
            printf("yshell: History refreshed\n");
        }
        close(history_fd);
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


