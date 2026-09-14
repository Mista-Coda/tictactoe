#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"


int main(int argc, char** argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);

    bool enableDebug = false;
    bool run = false;
    if (argc > 1) {
        const char* firstArg = argv[1];
        if (strcmp("debug", firstArg) == 0) {
            enableDebug = true;
            nob_log(NOB_INFO, "Enabling debug");
        } else if (strcmp("run", firstArg) == 0) {
            run = true;
            nob_log(NOB_INFO, "Autorunning");
        }
    }

    Cmd buildCmd = {0};
    cmd_append(&buildCmd, "cc", "-Wall", "-Wextra", "-o", "tictactoe");
    if (enableDebug) {
        cmd_append(&buildCmd, "-ggdb");
    }
    
    cmd_append(&buildCmd, "src/main.c");
    cmd_append(&buildCmd, "src/terminal.c");
    cmd_append(&buildCmd, "src/tictactoe.c");
    cmd_append(&buildCmd, "src/minimax.c");
    cmd_append(&buildCmd, "src/nob.c");

    if (!cmd_run(&buildCmd)) return 1;

    if (run) {
        Cmd runCmd = {0};
        cmd_append(&runCmd, "./tictactoe");
        if (!cmd_run(&runCmd)) return 1;
    }

    return 0;
}