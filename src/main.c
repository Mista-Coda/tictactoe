#include <stdio.h>
#include <stdbool.h>

#include "terminal.h"
#include "tictactoe.h"
#include "minimax.h"
#include "../nob.h"

void user_turn(TicTacToeBoard* board, CellState userType) {
    bool placed = false;

    do {
        size_t position;
        printf("Enter your position: ");
        bool validEntry = scanf("%zu", &position);

        if (!validEntry || (position > 9 && position - 1 > 8) || position < 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        };

        position--;

        if (!is_position_free(board, position)) continue;

        size_t row, col;
        pos_to_row_col(position, &row, &col);

        board->board[row][col] = userType;
        board->moveCount++;
        placed = true;
    } while(!placed);
}

int main() {
    terminal_enter_alt_buffer();
    TicTacToeBoard game = {0};
    bool isOver = false;
    while (!isOver) {
        terminal_clear();
        print_board(&game);
        user_turn(&game, CELL_CROSS);
        WinState winstate = check_for_win(&game);
        isOver = winstate != WIN_NO;
        if (isOver) break;

        terminal_clear();
        print_board(&game);
        size_t botPos = minimax_pick_position(&game, CELL_NAUGHT);
        size_t row, col;
        pos_to_row_col(botPos, &row, &col);
        game.board[row][col] = CELL_NAUGHT;
        game.moveCount++;
        winstate = check_for_win(&game);
        isOver = winstate != WIN_NO;
    }
    terminal_leave_alt_buffer();

    WinState winner = check_for_win(&game);
    print_board(&game);
    switch (winner) {
        case WIN_TIE: printf("Tie\n"); break;
        case WIN_CROSSES: printf("X Wins!\n"); break;
        case WIN_NAUGHTS: printf("0 Wins!\n"); break;
        default: NOB_UNREACHABLE("Should not break out of main loop with no win state"); break;
    }
    return 0;
}