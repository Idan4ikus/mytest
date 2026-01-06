#include "Board.h"
#include "Pawn.h"
#include "TheRook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Empty.h"
#include <cctype>

/// <summary>
/// sets the board at the begining stage
/// </summary>
Board::Board()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            board[i][j] = &em;

    for (int j = 0; j < 8; j++)
    {
        Pawn* wp = new Pawn();
        wp->color = 0;
        wp->hasMoved = false;
        wp->bd = this;
        wp->pose = std::string{ static_cast<char>('a' + j), '2' };
        board[1][j] = wp;

        Pawn* bp = new Pawn();
        bp->color = 1;
        bp->hasMoved = false;
        bp->bd = this;
        bp->pose = std::string{ static_cast<char>('a' + j), '7' };
        board[6][j] = bp;
    }

    Piece* whitePieces[8] =
    {
        new TheRook(), new Knight(), new Bishop(), new Queen(),
        new King(), new Bishop(), new Knight(), new TheRook()
    };
    Piece* blackPieces[8] = 
    {
        new TheRook(), new Knight(), new Bishop(), new Queen(),
        new King(), new Bishop(), new Knight(), new TheRook()
    };

    for (int j = 0; j < 8; j++)
    {
        whitePieces[j]->color = 0;
        whitePieces[j]->hasMoved = false;
        whitePieces[j]->bd = this;
        whitePieces[j]->pose = std::string{ static_cast<char>('a' + j), '1' };
        board[0][j] = whitePieces[j];

        blackPieces[j]->color = 1;
        blackPieces[j]->hasMoved = false;
        blackPieces[j]->bd = this;
        blackPieces[j]->pose = std::string{ static_cast<char>('a' + j), '8' };
        board[7][j] = blackPieces[j];
    }

    em.bd = this;
    lastEatedPiece = &em;
    currPlayer = 0;
}

/// <summary>
/// updates the board
/// </summary>
/// <param name="curr"></param>
/// <param name="dest"></param>
/// <returns></returns>
Board Board::UpdateBoard(std::string curr, std::string dest)
{
    int srcCol = converter(curr[0]);
    int srcRow = curr[1] - '1';
    int dstCol = converter(dest[0]);
    int dstRow = dest[1] - '1';

    lastEatedPiece = board[dstRow][dstCol];

    Piece* moving = board[srcRow][srcCol];
    moving->hasMoved = true;
    moving->pose = dest;

    board[dstRow][dstCol] = moving;
    board[srcRow][srcCol] = &em;

    currPlayer = 1 - currPlayer;
    return *this;
}

/// <summary>
/// converts the char to the right int
/// </summary>
/// <param name="ch"></param>
/// <returns></returns>
int Board::converter(char ch)
{
    return std::tolower(ch) - 'a';   
}

/// <summary>
/// cheks which piece is in the place it gets
/// </summary>
/// <param name="place"></param>
/// <returns></returns>
Piece* Board::checkpiece(std::string place)
{
    int col = converter(place[0]);
    int row = place[1] - '1';
    return board[row][col];
}
/// <summary>
/// searches for the king in the color it gets
/// </summary>
/// <param name="color"></param>
/// <returns></returns>

std::string Board::WhereKing(int color)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j]->isKing() && board[i][j]->color == color)
            {
                return std::string{ static_cast<char>('a' + j), static_cast<char>('1' + i) };
            }
        }
    }
    return "";
}
/// <summary>
/// checks if check on the king in the color it gets
/// </summary>
/// <param name="color"></param>
/// <returns></returns>
bool Board::isCheck(int color)
{
    std::string KP = WhereKing(color);
    if (KP.empty())
        return false;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (!board[i][j]->isEmpty())
            {
                if (board[i][j]->color != color)
                {
                    std::string from{ static_cast<char>('a' + j), static_cast<char>('1' + i) };
                    if (board[i][j]->isValidMove(from, KP) == 0)
                    {
                        return true;
                    }

                }
            }
        }
    }
    return false;
}

/// <summary>
/// undoes the last move that happens for checks 
/// </summary>
/// <param name="curr"></param>
/// <param name="dst"></param>
/// <returns></returns>
Board Board::undoMove(std::string curr, std::string dst)
{
    int srcCol = converter(curr[0]);
    int srcRow = curr[1] - '1';
    int dstCol = converter(dst[0]);
    int dstRow = dst[1] - '1';

    Piece* p1 = board[dstRow][dstCol];
    board[srcRow][srcCol] = p1;
    p1->pose = curr;
    Piece* p2 = lastEatedPiece;
    board[dstRow][dstCol] = p2;
    currPlayer = 1 - currPlayer;
    
    return *this;
}


int Board::isLegalMove(std::string curr, std::string dest)
{
    if (!inBounds(curr) || !inBounds(dest))
        return 5;

    if (curr == dest)
        return 7;

    Piece* dstP = checkpiece(dest);
    Piece* srcP = checkpiece(curr);

    if (srcP->isEmpty() || srcP->color != currPlayer)
        return 2;

    if (!dstP->isEmpty() && srcP->color == dstP->color)
        return 3;

    int moveCheck = srcP->isValidMove(curr, dest);
    if (moveCheck != 0)
        return moveCheck;

    int movingColor = currPlayer;
    Piece* prevLast = lastEatedPiece;
    bool wasMoved = srcP->hasMoved;

    UpdateBoard(curr, dest);

    if (isCheck(movingColor))
    {
        undoMove(curr, dest);
        srcP->hasMoved = wasMoved;
        lastEatedPiece = prevLast;
        currPlayer = movingColor;
        return 4;
    }

    bool opponentInCheck = isCheck(currPlayer);
    int result = opponentInCheck ? 1 : 0;

    if (opponentInCheck && isCheckmate(currPlayer))
        result = 8;

    return result;
}

bool Board::inBounds(const std::string& pos) const
{
    return pos.length() == 2 &&
        std::tolower(pos[0]) >= 'a' && std::tolower(pos[0]) <= 'h' &&
        pos[1] >= '1' && pos[1] <= '8';
}

int Board::simulateMove(std::string curr, std::string dest, int color)
{
    if (!inBounds(curr) || !inBounds(dest))
        return 5;

    if (curr == dest)
        return 7;

    Piece* dstP = checkpiece(dest);
    Piece* srcP = checkpiece(curr);

    if (srcP->isEmpty() || srcP->color != color)
        return 2;

    if (!dstP->isEmpty() && srcP->color == dstP->color)
        return 3;

    int moveCheck = srcP->isValidMove(curr, dest);
    if (moveCheck != 0)
        return moveCheck;

    int savedPlayer = currPlayer;
    Piece* savedLast = lastEatedPiece;
    bool wasMoved = srcP->hasMoved;

    UpdateBoard(curr, dest);

    int res;
    if (isCheck(color))
        res = 4;
    else
        res = isCheck(currPlayer) ? 1 : 0;

    undoMove(curr, dest);
    srcP->hasMoved = wasMoved;
    lastEatedPiece = savedLast;
    currPlayer = savedPlayer;

    return res;
}

bool Board::hasAnyLegalMove(int color)
{
    int savedPlayer = currPlayer;
    Piece* savedLast = lastEatedPiece;
    currPlayer = color;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Piece* p = board[i][j];
            if (p->isEmpty() || p->color != color)
                continue;

            std::string src{ static_cast<char>('a' + j), static_cast<char>('1' + i) };

            for (int r = 0; r < 8; r++)
            {
                for (int c = 0; c < 8; c++)
                {
                    std::string dst{ static_cast<char>('a' + c), static_cast<char>('1' + r) };
                    if (src == dst)
                        continue;

                    int code = simulateMove(src, dst, color);
                    if (code == 0 || code == 1)
                    {
                        currPlayer = savedPlayer;
                        lastEatedPiece = savedLast;
                        return true;
                    }
                }
            }
        }
    }

    currPlayer = savedPlayer;
    lastEatedPiece = savedLast;
    return false;
}

bool Board::isCheckmate(int color)
{
    if (!isCheck(color))
        return false;

    return !hasAnyLegalMove(color);
}
