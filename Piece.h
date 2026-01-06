#pragma once
#include <string>

class Board;

class Piece {
public:
	int color = 0;
	std::string type;
	bool hasMoved = false;
	std::string pose;
	Board* bd = nullptr;

	virtual ~Piece() = default;
	virtual int isValidMove(std::string curr, std::string dest);
	virtual int checkEat(std::string curr, std::string dest);
	virtual bool isEmpty();
	virtual bool isKing();
};
