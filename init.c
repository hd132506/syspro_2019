#include "yshell.h"
#include <pwd.h>
#include <signal.h>


extern char *username, hostname[HOST_NAME_MAX], directory[PATH_MAX];
extern int n_commands;

void refresh_history();

/* Initial function for getting user and host information */
void init(void) {
    pid_t c_pid;
    struct passwd *user_pw;

    /* Block ^C signal */
    sigset_t mask;
    if(sigemptyset(&mask) == -1 || sigaddset(&mask, SIGINT) == -1 || sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
        perror("Failed to initialize signal mask\n");
        exit(1);
    }
    

    /* Get user, host name and current working directory */
    gethostname(hostname, HOST_NAME_MAX);
    user_pw = getpwuid(getuid());
    username = strdup(user_pw->pw_name);
    getcwd(directory, sizeof(directory));

    /* create history file*/
    refresh_history();

    /* clear screen */
    c_pid = fork();
    if(c_pid < 0)
        perror("Fork failed\n");
    else if(c_pid == 0)
        execlp("clear", "clear", NULL);
    else
        wait(NULL);
}

/* Defined as function for other usage */
void refresh_history() {
    int history_fd = creat(".yhistory", 0644);
    if(history_fd == -1) {
        perror("Failed to create history file\n");
        exit(1);
    }
    n_commands = 0;
    close(history_fd);    
}
