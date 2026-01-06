#include "Piece.h"
#pragma once

class Bishop : public Piece
{
public:
	int isValidMove(std::string curr, std::string dest) override;
	int checkEat(std::string curr, std::string dest) override;
	bool isEmpty() { return false; }
	bool isKing() { return false; }
};