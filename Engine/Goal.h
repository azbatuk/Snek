#pragma once

#include "Snake.h"
#include "Board.h"
//#include "Obstacles.h"
#include <random>

class Goal
{
public:
	//Goal(std::mt19937& rng, Board& brd, const Snake& snake, const Obstacles& obs);
	Goal(std::mt19937& rng, Board& brd, const Snake& snake);
	//void Respawn(std::mt19937& rng, Board& brd, const Snake& snake, const Obstacles& obs);
	void Respawn(std::mt19937& rng, Board& brd, const Snake& snake);
	void Draw(Board& brd) const;
	const Location& GetLocation() const;
private:
	static constexpr Color c = Colors::Red;
	Location loc;
};