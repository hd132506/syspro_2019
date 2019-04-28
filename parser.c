#include "yshell.h"

int do_nothing;
extern int should_run;

char* find_delimiter(char **delimiter, char *command);

void parse_command(char **command) {
    /* Process empty/exit command */
    do_nothing = 0;
    pre_parse(*command);

    if(!should_run || do_nothing) return;

    char *args[100], *delimiter = malloc(3*sizeof(char));
    /* 1. Find a delimiter and its position.
       2. Decide where the next cmd starts from the previous info.
       3. Change the delimiters to space for tokenizing 
       4. Repeat untill no next command found */

    char *current_cmd = *command, *next_cmd; 
    next_cmd = find_delimiter(&delimiter, current_cmd);
    do {
        int i;
        for(i = 0; delimiter[i] != '\0'; ++i) {
           *(next_cmd-i-1) = ' ';
        }

        /* Tokenize */
        int idx = 0;
        char *p = strtok(current_cmd, " \n");
        while(p != NULL && p < next_cmd) {
            args[idx++] = strdup(p);
            p = strtok(NULL, " \n");
        }
        args[idx] = NULL;
        current_cmd = next_cmd;
        next_cmd = find_delimiter(&delimiter, current_cmd); 

        /* Run */ 
        pid_t pid = exec_command(args);
        if(strcmp(delimiter, "&")) {
            waitpid(pid, NULL, 0);
        }
    } while(*current_cmd != '\0' && *current_cmd != '\n');

    free(delimiter);
}

void pre_parse(char *command) {
    if(*command == '\n') {
        do_nothing = 1;
    }
    else if(!strcmp(command, "exit\n"))
        should_run = 0;
}

/* Find delimiter and return the position right after it */
char* find_delimiter(char **delimiter, char *command) {
    char *pos;
    int find, del_len = 0;
    memset(*delimiter, 0, sizeof(*delimiter));
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
