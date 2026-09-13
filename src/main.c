#include <stdio.h>
#include <stdbool.h>

#include "terminal.h"

typedef enum {
    CELL_EMPTY,
    CELL_CROSS,
    CELL_NAUGHT,
} CellState;

typedef struct {
    size_t moveCount;
    CellState board[3][3];
} TicTacToeBoard;

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

CellState check_for_win(const TicTacToeBoard* game) {
    for (size_t r = 0; r < 3; ++r) {
        if (game->board[r][0] != CELL_EMPTY &&
        game->board[r][0] == game->board[r][1] &&
        game->board[r][1] == game->board[r][2]) {
            return game->board[r][0];
        }
    }

    for (size_t c = 0; c < 3; ++c) {
        if (game->board[0][c] != CELL_EMPTY &&
        game->board[0][c] == game->board[1][c] &&
        game->board[1][c] == game->board[2][c]) {
            return game->board[0][c];
        }
    }

    if (game->board[0][0] != CELL_EMPTY &&
        game->board[0][0] == game->board[1][1] &&
        game->board[1][1] == game->board[2][2]) {
            return game->board[0][0];
    }

    if (game->board[0][2] != CELL_EMPTY &&
        game->board[0][2] == game->board[1][1] &&
        game->board[1][1] == game->board[2][0]) {
            return game->board[0][2];
    }

    return CELL_EMPTY;
}

int main() {
    terminal_enter_alt_buffer();
    TicTacToeBoard game = {0};
    bool isOver = false;
    while (!isOver) {
        terminal_clear();
        print_board(&game);
        user_turn(&game, CELL_CROSS);
        isOver = check_for_win(&game) != CELL_EMPTY || game.moveCount >= 9;
    }
    terminal_leave_alt_buffer();

    CellState winner = check_for_win(&game);
    print_board(&game);
    switch (winner) {
        case CELL_EMPTY: printf("Tie\n"); break;
        case CELL_CROSS: printf("X Wins!\n"); break;
        case CELL_NAUGHT: printf("0 Wins!\n"); break;
    }
    return 0;
}