#pragma once
#include <string>
#include "Empty.h"

class Piece;

class Board {
public:
    Piece* board[8][8];   
    Piece* lastEatedPiece;
    Empty em;
    int currPlayer;

    Board();

    Board UpdateBoard(std::string curr, std::string dest);
	std::string WhereKing(int color);
    Piece* checkpiece(std::string place);
    int converter(char ch);
    bool isCheck(int color);
    int isLegalMove(std::string curr, std::string dest);
    Board undoMove(std::string curr, std::string dest);
    bool inBounds(const std::string& pos) const;
    bool isCheckmate(int color);
    bool hasAnyLegalMove(int color);
    int simulateMove(std::string curr, std::string dest, int color);

};
