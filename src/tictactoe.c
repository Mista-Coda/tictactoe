#include "tictactoe.h"

#include <stdio.h>

char cell_icons[] = {
    [CELL_EMPTY] = ' ',
    [CELL_CROSS] = 'X',
    [CELL_NAUGHT] = '0',
};

void print_board(const TicTacToeBoard* board) {
    printf("%c | %c | %c\n",
        cell_icons[board->board[0][0]],
        cell_icons[board->board[0][1]],
        cell_icons[board->board[0][2]]
    );
    printf("---------\n");
    printf("%c | %c | %c\n",
        cell_icons[board->board[1][0]],
        cell_icons[board->board[1][1]],
        cell_icons[board->board[1][2]]
    );
    printf("---------\n");
    printf("%c | %c | %c\n",
        cell_icons[board->board[2][0]],
        cell_icons[board->board[2][1]],
        cell_icons[board->board[2][2]]
    );
}

void pos_to_row_col(size_t position, size_t* row, size_t* col) {
    *row = position / 3;
    *col = position % 3;
}


bool is_position_free(TicTacToeBoard* board, size_t position) {
    size_t row, col;
    pos_to_row_col(position, &row, &col);
    CellState cellState = board->board[row][col];
    return (cellState == CELL_EMPTY);
}

WinState check_for_win(const TicTacToeBoard* game) {
    for (size_t r = 0; r < 3; ++r) {
        if (game->board[r][0] != CELL_EMPTY &&
        game->board[r][0] == game->board[r][1] &&
        game->board[r][1] == game->board[r][2]) {
            return (WinState)game->board[r][0];
        }
    }

    for (size_t c = 0; c < 3; ++c) {
        if (game->board[0][c] != CELL_EMPTY &&
        game->board[0][c] == game->board[1][c] &&
        game->board[1][c] == game->board[2][c]) {
            return (WinState)game->board[0][c];
        }
    }

    if (game->board[0][0] != CELL_EMPTY &&
        game->board[0][0] == game->board[1][1] &&
        game->board[1][1] == game->board[2][2]) {
            return (WinState)game->board[0][0];
    }

    if (game->board[0][2] != CELL_EMPTY &&
        game->board[0][2] == game->board[1][1] &&
        game->board[1][1] == game->board[2][0]) {
            return (WinState)game->board[0][2];
    }

    if (game->moveCount > 8) {
        return WIN_TIE;
    }

    return WIN_NO;
}