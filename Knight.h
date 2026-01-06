#include "Piece.h"
#pragma once

class Knight : public Piece
{
public:
	int isValidMove(std::string curr, std::string dest);
	int checkEat(std::string curr, std::string dest);
	bool isEmpty() { return false; }
	bool isKing() { return false; }
};