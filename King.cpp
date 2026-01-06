#pragma once
#include "King.h"
#include "string.h"

int King::isValidMove(std::string curr, std::string dest)
{
	if (curr == dest)
		return 7;


	char currCol = std::tolower(curr[0])-'a';
	char destCol = std::tolower(dest[0])-'a';
	char currRow = curr[1]-'1';
	char destRow = dest[1]-'1';

	int destRowCheck = std::abs(destRow - currRow);
	int destColCheck = std::abs(destCol - currCol);

	if (destRowCheck > 1 || destColCheck  > 1)
		return 6;

	return 0;
}


int King::checkEat(std::string curr, std::string dest) { return isValidMove(curr,dest); }

bool isEmpty() { return false; }