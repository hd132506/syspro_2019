#include "yshell.h"

/* Flags for control main logic */
int should_run = 1;

int main(void) {
    init();
    while(should_run) {
        char *cmd;
        print_prompt();
        read_command(&cmd);
        parse_command(&cmd);
        free(cmd);
    }

    printf("yshell closed.\n");
    return 0;
}
