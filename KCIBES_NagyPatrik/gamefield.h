#pragma once
#include <cstdint>
#include "cell.h"
#include <vector>
#include <iostream>


class GameField {
public:
	GameField(const uint16_t a);
	GameField(const uint16_t a, const double chance);
	GameField(const uint16_t a, const uint16_t b);
	GameField(const uint16_t a, const uint16_t b, const double chance);
	GameField(const uint16_t height, const uint16_t width, const uint16_t top, const uint16_t left, const std::vector<std::vector<Cell>>& Vector);
	std::vector<std::vector<Cell>> VectorGenerate(const uint16_t a, const uint16_t b, const double chance) const;

	std::vector<std::vector<Cell>> GetGameField() const;

	void LifeSetup();
	void CheckAround(int16_t i, int16_t j);
	char CheckIndex(const int16_t i, const int16_t j) const;
	void ShouldThisCellLive(Cell& cell, std::vector<std::vector<char>>& v1);
	void GameStart();
	bool IsThereAnyAlive() const;

	friend std::ostream& operator<<(std::ostream& os, const GameField& other);
private:
	std::vector<std::vector<Cell>> mGameField;
};