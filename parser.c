#include "yshell.h"

extern int do_something, should_run;

char* find_delimiter(char (*delimiter)[3], char *command);

void parse_command(char *(*args)[100], char (*delimiter)[3], char **command) {
    /* Process empty/exit command */
    pre_parse(*command);
    if(!should_run) return;
    /* 1. Find a delimiter and its position.
       2. Decide where the next cmd starts from the previous info.
       3. Change the delimiters to space for tokenizing */
    char *next_cmd = find_delimiter(delimiter, *command);
    int i;
    for(i = 0; (*delimiter)[i] != '\0'; ++i) {
        *(next_cmd-i-1) = ' ';
    }

    /* Tokenize */
    char *p = strtok(*command, " \n");
    int idx = 0;
    while(p != NULL && p < next_cmd) {
        (*args)[idx++] = strdup(p);
        p = strtok(NULL, " \n");
    }
    (*args)[idx] = NULL;

    *command = next_cmd;
}

void pre_parse(char *command) {
    if(*command == '\n')
        do_something = 0;
    if(!strcmp(command, "exit\n"))
        should_run = do_something = 0;
}

/* Find delimiter and return the position right after it */
char* find_delimiter(char (*delimiter)[3], char *command) {
    char *pos;
    int find, del_len = 0;
    /* Default value of find flag is 1 because it's easier to deal with in switch  block */
    for(pos = command; *pos != '\0'; ++pos) {
        find = 1;
        switch(*pos) {
            case ';':
                strcpy(*delimiter, ";"); del_len = 1;
                break;
            case '&':
                /*TODO: Process "&&" */
                strcpy(*delimiter, "&"); del_len = 1;
                break;
            default:
                find = 0;
        }
        if(find) break;
    }
    return pos + del_len;
}
