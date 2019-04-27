#include "yshell.h"

extern int do_something, should_run;

void parse_command(char *(*args)[100], char *command) {
    pre_parse(command);
    if(!should_run) return;
    char *p = strtok(command, " \n");
    int idx = 0;

    while(p != NULL) {
        (*args)[idx++] = strdup(p);
        p = strtok(NULL, " \n");
    }
    (*args)[idx] = NULL;
}

void pre_parse(char *command) {
    if(*command == '\n')
        do_something = 0;
    if(!strcmp(command, "exit\n"))
        should_run = do_something = 0;
}
