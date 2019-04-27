#include "yshell.h"
#include <pwd.h>

/* Initial function for getting user and host information */
void init(void) {
    pid_t c_pid;
    gethostname(hostname, HOST_NAME_MAX);
 
    c_pid = fork();
    if(c_pid < 0)
        perror("Fork failed\n");
    else if(c_pid == 0)
        execlp("clear", "clear", NULL);
    else
        wait(NULL);
}
