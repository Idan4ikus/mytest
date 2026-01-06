#pragma once 
#include "Queen.h"
#include "Piece.h"
#include "Board.h"

int Queen::isValidMove(std::string curr, std::string dest)
{
    if (curr == dest)
        return 7;

    int srcRow = curr[1] - '1';
    int srcCol = std::tolower(curr[0]) - 'a';

    int dstRow = dest[1] - '1';
    int dstCol = std::tolower(dest[0]) - 'a';

    int DRow = dstRow - srcRow;
    int DCol = dstCol - srcCol;

    bool rookMove = (srcRow == dstRow || srcCol == dstCol);
    bool bishopMove = (std::abs(DRow) == std::abs(DCol));

    if (!rookMove && !bishopMove)
        return 6;

    int stepRow = (DRow == 0) ? 0 : (DRow > 0 ? 1 : -1);
    int stepCol = (DCol == 0) ? 0 : (DCol > 0 ? 1 : -1);

    int row = srcRow + stepRow;
    int col = srcCol + stepCol;

    while (row != dstRow || col != dstCol)
    {
        if (!bd->board[row][col]->isEmpty())
            return 6;

        row += stepRow;
        col += stepCol;
    }

    return 0; 
}

int Queen::checkEat(std::string curr, std::string dst) { return isValidMove(curr, dst); }
