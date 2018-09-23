#pragma once
#include "Board.h"
#include "Snake.h"
#include <random>

class Obstacles
{
	class Obstacle
	{
	public:
		void Draw(Board& brd) const;
		Location GetLocation() const;
		void InitObstacle(Location& in_loc);
	private:
		Location loc;
	};
public:
	void Draw(Board& brd) const;
	void AddObstacle(std::mt19937 & rng, Board & brd, const Snake & snake);
	bool IsInTile(const Location& target) const;
	bool IsObstacleHit(const Location& target) const;
private:
	static constexpr Color c = Colors::Gray;
	static constexpr int nObstaclesMax = 100;
	Obstacle ObstacleSet[nObstaclesMax];
	int nObstacles = 0;
};