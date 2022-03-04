#include "gamefield.h"
#include <vector>
#include <iostream>

GameField::GameField(const uint16_t a)
{
	mGameField = VectorGenerate(a, a, 0.10);
}

GameField::GameField(const uint16_t a, const double chance)
{
	mGameField = VectorGenerate(a, a, chance);
}

GameField::GameField(const uint16_t a, const uint16_t b)
{
	mGameField = VectorGenerate(a, b, 0.10);
}

GameField::GameField(const uint16_t a, const uint16_t b, const double chance)
{
	mGameField = VectorGenerate(a, b, chance);
}

GameField::GameField(const uint16_t height, const uint16_t width, const uint16_t top, const uint16_t left, const std::vector<std::vector<Cell>>& Vector)
{
	mGameField = VectorGenerate(height, width, 0);
	uint16_t i = top;
	uint16_t j = left;
	uint16_t i2 = Vector.size();
	uint16_t j2 = Vector[0].size();

	uint16_t copyi = 0;
	uint16_t copyj = 0;
	while (i < top + i2)
	{
		j = left;
		copyj = 0;
		while (j < left + j2)
		{
			mGameField[i][j] = Vector[copyi][copyj];
			j++;
			copyj++;
		}
		i++;
		copyi++;
	}
}

std::vector<std::vector<Cell>> GameField::GetGameField() const
{
	return mGameField;
}

std::vector<std::vector<Cell>> GameField::VectorGenerate(const uint16_t a, const uint16_t b, const double chance) const
{
	std::vector<std::vector<Cell>> v1;
	for (uint16_t i = 0; i < a; i++) {
		std::vector<Cell> v2;
		for (uint16_t j = 0; j < b; j++) {
			v2.push_back(Cell(chance));
		}
		v1.push_back(v2);
	}
	return v1;
}

std::ostream& operator<<(std::ostream& os, const GameField& other)
{
	for (int i = 0; i < other.mGameField.size(); i++) {
		for (int j = 0; j < other.mGameField[i].size(); j++)
		{
			os << (other.mGameField[i][j].GetAlive() ? 'O' : '-' ) << " ";
		}
		os << std::endl;
	}
	return os;
}

void GameField::LifeSetup()
{
	for (int i = 0; i < mGameField.size(); i++) {
		for (int j = 0; j < mGameField[i].size(); j++)
		{
			CheckAround(i, j);
		}
	}
}

void GameField::CheckAround(const int16_t index, const int16_t index2)
{
	// -1,1  0,1  1,1
	// -1,0  0,0  1,0
	// -1,-1 0,-1 1,-1
	int8_t i = index - 1;
	int8_t j = index2 - 1;

	std::vector<std::vector<char>> v1;
	int8_t i2 = i + 3;
	int8_t j2 = j + 3;
	while (i < i2)
	{
		std::vector<char> v2;
		j = index2 - 1;
		while (j < j2)
		{
			v2.push_back(CheckIndex(i, j));
			j++;
		}
		v1.push_back(v2);
		i++;
	}
	ShouldThisCellLive(mGameField[index][index2], v1);
}

char GameField::CheckIndex(const int16_t i, const int16_t j) const
{
	if ((i >= 0 && j >= 0 && i <= mGameField.size() - 1 && j <= mGameField[i].size() - 1))
	{
		if (mGameField[i][j].GetAlive())
		{
			return 'O';
		}
		else
		{
			return 'X';
		}
	}
	else
	{
		return 'X';
	}
}

void GameField::ShouldThisCellLive(Cell& cell, std::vector<std::vector<char>>& v1)
{
	int8_t counter = 0;
	for (int i = 0; i < v1.size(); i++) {
		for (int j = 0; j < v1[i].size(); j++)
		{
			if (v1[i][j] == 'O')
			{
				counter++;
			}
		}
	}
	;
	if (v1[1][1] == 'O')
	{
		counter--;
	}
	if (counter == 3 && !cell.GetAlive())
	{
		cell.SetAlive(true);
	}
	if (counter < 2 || counter > 3)
	{
		cell.SetAlive(false);
	}
}

void GameField::GameStart()
{
	size_t i = 0;
	std::cout << *this;
	std::cin.get();
	while (IsThereAnyAlive() && i < 100)
	{
		system("CLS");
		LifeSetup();
		std::cout << *this;
		std::cin.get();
		std::cout << std::endl;
		i++;
	}
	if (i < 99)
	{
		std::cout << "A játék véget ért, meghalt az összes sejt!" << std::endl;
	}
	else
	{
		std::cout << "A játék véget ért, mert elérte a 100 lépést!" << std::endl;
	}
}

bool GameField::IsThereAnyAlive() const
{
	uint16_t counter = 0;
	for (int i = 0; i < mGameField.size(); i++) {
		for (int j = 0; j < mGameField[i].size(); j++)
		{
			if (mGameField[i][j].GetAlive())
			{
				counter++;
			}
		}
	}
	return counter > 0;
}





