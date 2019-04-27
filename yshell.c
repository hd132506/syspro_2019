#include "yshell.h"

/* Flags for control main logic */
int should_run = 1, do_something = 1;

int main(void) {
    init();
    while(should_run) {
        char *cmd;
        char *args[100]; /* Command line arguments */

        print_prompt();
        read_command(&cmd);
        parse_command(&args, cmd);
       
        if(do_something)
            exec_command(args);

        do_something = 1;
        free(cmd);

    }

    printf("yshell closed.\n");
    return 0;
}
