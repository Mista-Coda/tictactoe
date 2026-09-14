#include "minimax.h"

#include "../nob.h"

#define BOARD_SIZE 9

void copy_board(const TicTacToeBoard* source, TicTacToeBoard* dest) {
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        size_t row, col;
        pos_to_row_col(i, &row, &col);

        dest->board[row][col] = source->board[row][col];
    }

    dest->moveCount = source->moveCount;
}

static CellState other_turn(CellState turn) {
    if (turn == CELL_CROSS) {
        return CELL_NAUGHT;
    }

    return CELL_CROSS;
}

int calculate_score_position(
    TicTacToeBoard* game,
    size_t position,
    CellState turn
) {
    size_t row, col;
    pos_to_row_col(position, &row, &col);

    game->board[row][col] = turn;
    game->moveCount++;

    WinState win = check_for_win(game);

    if (win == (WinState)turn) {
        return 1;
    }

    if (game->moveCount >= BOARD_SIZE) {
        return 0;
    }

    CellState opponent = other_turn(turn);

    int bestScore = INT_MIN;
    bool foundMove = false;

    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        size_t nextRow, nextCol;
        pos_to_row_col(i, &nextRow, &nextCol);

        if (game->board[nextRow][nextCol] != CELL_EMPTY) {
            continue;
        }

        foundMove = true;

        TicTacToeBoard working = {0};
        copy_board(game, &working);

        int score = calculate_score_position(
            &working,
            i,
            opponent
        );

        score = -score;

        if (!foundMove || score > bestScore) {
            bestScore = score;
        }
    }

    return bestScore;
}

size_t minimax_pick_position(
    const TicTacToeBoard* game,
    CellState turn
) {
    size_t freePositionCount = 0;

    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        size_t row, col;
        pos_to_row_col(i, &row, &col);

        if (game->board[row][col] == CELL_EMPTY) {
            freePositionCount++;
        }
    }

    if (freePositionCount == 0) {
        assert(false);
        return 0;
    }

    size_t possiblePositions[freePositionCount];
    size_t addedPositions = 0;

    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        size_t row, col;
        pos_to_row_col(i, &row, &col);

        if (game->board[row][col] == CELL_EMPTY) {
            possiblePositions[addedPositions++] = i;
        }
    }

    size_t finalPos = possiblePositions[0];
    int finalPosScore = INT_MIN;

    for (size_t i = 0; i < freePositionCount; ++i) {
        size_t pos = possiblePositions[i];

        TicTacToeBoard working = {0};
        copy_board(game, &working);

        int score = calculate_score_position(
            &working,
            pos,
            turn
        );

        nob_log(
            NOB_INFO,
            "position=%zu score=%d",
            pos,
            score
        );

        if (score > finalPosScore) {
            finalPos = pos;
            finalPosScore = score;
        }
    }

    return finalPos;
}