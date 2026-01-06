#pragma once
#include "Piece.h"
class Empty : public Piece {
public:
	int isValidMove(std::string curr, std::string dest) override;
	int	checkEat(std::string curr, std::string dest) override;
	bool isEmpty() override { return true; }
	bool isKing() override { return false; }
};
