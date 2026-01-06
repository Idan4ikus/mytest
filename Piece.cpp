#include "Piece.h"

int Piece::isValidMove(std::string curr, std::string dest)
{
    return curr == dest ? 7 : 6;
}

int Piece::checkEat(std::string curr, std::string dest)
{
    return isValidMove(curr, dest);
}

bool Piece::isEmpty()
{
    return false;
}

bool Piece::isKing()
{
    return false;
}
