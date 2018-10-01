#include "Goal.h"

Goal::Goal(std::mt19937 & rng, Board & brd, const Snake & snake)
{
	Respawn(rng, brd, snake);
}

void Goal::Respawn(std::mt19937 & rng, Board & brd, const Snake & snake)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);

	Location newLoc;

	// Generate a random location. 
	// And if it is occupied by Snake OR another Goal OR an Obstacle OR a Poison,
	// then keep generating a new location until you get one that is not occupied.
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc) || brd.CheckForGoal(newLoc) || brd.CheckForObstacle(newLoc) || brd.CheckForPoison(newLoc));

	brd.AddGoal(newLoc);
}
