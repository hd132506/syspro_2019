#include "yshell.h"

/* Flags for control main logic */
int run_shell = 1;

int main(void) {
    init();
    while(run_shell) {
        char *cmd;
        print_prompt();
        read_command(&cmd);
        parse_command(&cmd);
        free(cmd);
    }
    printf("yshell closed.\n");
    return 0;
}
