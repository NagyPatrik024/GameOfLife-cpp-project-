#include <iostream>
#include "gamefield.h"



int main()
{
	uint16_t a = 20;
	uint16_t b = 20;
	uint16_t a2 = 6;
	uint16_t b2 = 6;
	uint16_t top = 7;
	uint16_t left = 7;
	double chance = 0.5;

	GameField gf1 = GameField(a2, b2,chance);
	GameField gf2 = GameField(a, b, top, left, gf1.GetGameField());
	gf2.GameStart();
}

