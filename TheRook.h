#include "Piece.h"
#pragma once

class TheRook : public Piece
{
public:
	int isValidMove(std::string curr, std::string dest);
	int checkEat(std::string curr, std::string dest);
};