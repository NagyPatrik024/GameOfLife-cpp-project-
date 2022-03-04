#include "cell.h"
#include "random"

Cell::Cell(double chance)
{
	std::random_device rnd;
	std::default_random_engine re(rnd());
	std::uniform_real_distribution<double> normal_dist(0, 1);

	mAlive = normal_dist(re) <= chance ? true : false;
}

void Cell::SetAlive(bool b)
{
	mAlive = b;
}

bool Cell::GetAlive() const
{
	return mAlive;
}





