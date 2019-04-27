#include "yshell.h"

/* Flags for control main logic */
int should_run = 1, do_something = 1;

int main(void) {
    init();
    while(should_run) {
        char *cmd, *cmd_ptr;
        char *args[100]; /* Command line arguments */

        print_prompt();
        read_command(&cmd);

        cmd_ptr = cmd;
        while(do_something) {
            char delimiter[3] = {};
            parse_command(&args, &delimiter, &cmd_ptr);
            if(!do_something) break;
            exec_command(args, delimiter);
        }
        do_something = 1;
        free(cmd);
    }

    printf("yshell closed.\n");
    return 0;
}
