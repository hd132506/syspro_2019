#include "yshell.h"
#include <pwd.h>

extern char *username, hostname[HOST_NAME_MAX], directory[PATH_MAX];

/* Initial function for getting user and host information */
void init(void) {
    pid_t c_pid;
    struct passwd *user_pw;

    gethostname(hostname, HOST_NAME_MAX);
    user_pw = getpwuid(getuid());
    username = strdup(user_pw->pw_name);
    getcwd(directory, sizeof(directory));

    /* clear screen */
    c_pid = fork();
    if(c_pid < 0)
        perror("Fork failed\n");
    else if(c_pid == 0)
        execlp("clear", "clear", NULL);
    else
        wait(NULL);
}
