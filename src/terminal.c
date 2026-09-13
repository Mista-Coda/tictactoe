#include "terminal.h"
#include <stdio.h>

void terminal_enter_alt_buffer() {
    printf("\033[?1049h");
    printf("\033[2J\033[H");
    fflush(stdout);
}

void terminal_leave_alt_buffer() {
    printf("\033[?1049l");
    fflush(stdout);
}

void terminal_clear() {
    printf("\033[2J\033[H");
}