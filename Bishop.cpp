#include <cmath>
#include <cctype>
#include "Bishop.h"
#include "Board.h"

int Bishop::isValidMove(std::string curr , std::string dest)
{
	if (curr == dest)
		return 7;


	int currRow = curr[1] - '1';
	int dstRow = dest[1] - '1';
	int currCol = std::tolower(curr[0]) - 'a';
	int dstCol = std::tolower(dest[0]) - 'a';

	if (abs(dstCol - currCol) != abs(dstRow - currRow))
		return 6;

	int stepRow = (dstRow == currRow) ? 0 : (dstRow > currRow ? 1 : -1);
	int stepCol = (dstCol == currCol) ? 0 : (dstCol > currCol ? 1 : -1);

	int row = currRow + stepRow;
	int col = currCol + stepCol;

	while (row != dstRow || col != dstCol)
	{
		if (!bd->board[row][col]->isEmpty())
			return 6;

		row += stepRow;
		col += stepCol;
	}

	return 0;
}

int Bishop::checkEat(std::string curr, std::string dst) { return isValidMove(curr , dst); }
