#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef enum {
    CELL_EMPTY,
    CELL_CROSS,
    CELL_NAUGHT,
} CellState;

typedef enum {
    WIN_NO,
    // These 2 match directly to the above CellState enum
    // so that returning a cell state of cross or naught also
    // means they won.
    WIN_CROSSES, WIN_NAUGHTS,
    WIN_TIE,
} WinState;

typedef struct {
    size_t moveCount;
    CellState board[3][3];
} TicTacToeBoard;

void print_board(const TicTacToeBoard* board);
void pos_to_row_col(size_t position, size_t* row, size_t* col);
bool is_position_free(TicTacToeBoard* board, size_t position);
WinState check_for_win(const TicTacToeBoard* game);