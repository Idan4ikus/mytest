#pragma once 
#include <cmath>
#include "Knight.h"
#include "Piece.h"
#include "Board.h"

int isValidMove(std::string curr , std::string dst)
{
	if (curr == dst)
		return 7;

	int currRow = curr[1] - '1';
	int dstRow = dst[1] - '1';
	int currCol = std::tolower(curr[0]) - 'a';
	int dstCol = std::tolower(dst[0]) - 'a';

	int Drow =  abs(dstRow - currRow);
	int Dcol = abs(dstCol - currCol);
	
	int res = ((Drow == 2 && Dcol == 1) || (Drow == 1 && Dcol == 2)) ? 0 : 6;
	
	return res;
}

int checkEat(std::string curr, std::string dst) { return isValidMove(curr , dst); }
