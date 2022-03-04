#pragma once
#include <vector>
class Cell {
public:
	Cell(double chance);

	void SetAlive(bool b);
	bool GetAlive() const;

private:
	bool mAlive;
};