#include "Obstacles.h"

void Obstacles::Draw(Board & brd) const
{
	for (int i = 0; i < nObstacles; i++)
	{
		ObstacleSet[i].Draw(brd);
	}
}

void Obstacles::AddObstacle(std::mt19937 & rng, Board & brd, const Snake & snake)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);

	Location newLoc;

	// Generate a random location, and keep re-generating 
	// if it is occupied by Snake or another previously added
	// Obstacle until you get one that is not occupied.
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc) || IsInTile(newLoc));

	ObstacleSet[nObstacles].InitObstacle(newLoc);
	nObstacles++;
}

bool Obstacles::IsInTile(const Location & target) const
{
	for (int i = 0; i < nObstacles; i++)
	{
		if (ObstacleSet[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

bool Obstacles::IsObstacleHit(const Location& target) const
{
	for (int i = 0; i < nObstacles; i++)
	{
		if (ObstacleSet[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

void Obstacles::Obstacle::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

Location Obstacles::Obstacle::GetLocation() const
{
	return loc;
}

void Obstacles::Obstacle::InitObstacle(Location & in_loc)
{
	loc = in_loc;
}
