#include "Board.h"
#include <assert.h>

/*
Snake class is Forward Declared in Board.h to avoid 
circular dependency since Snake.h is including Board.h
As a result, Snake.h is being included here instead of Board.h
*/
#include "Snake.h"

Board::Board(Graphics& in_gfx)
	:
	gfx(in_gfx)
{
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);

	Location loc;
	do {
		loc.x = xDist(rng);
		loc.y = yDist(rng);

		if (boardCells[loc.y * width + loc.x] == 0) // if cell is empty
		{
			boardCells[loc.y * width + loc.x] = 2; // insert poison
			nPoison--;
		}
	} while (nPoison > 0);
}

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	const int off_x = topLeftX + borderWidth + borderPadding;
	const int off_y = topLeftY + borderWidth + borderPadding;

	gfx.DrawRectDim(loc.x * cellDim + off_x + cellPadding, 
					loc.y * cellDim + off_y + cellPadding, 
					cellDim - cellPadding * 2, 
					cellDim - cellPadding * 2, 
					c);
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= 0 &&
		   loc.x < width &&
		   loc.y >= 0 &&
		   loc.y < height;
}

void Board::DrawBorder()
{
	// Calculate the coords of all 4 corners of the border
	const int top = topLeftY;
	const int left = topLeftX;
	const int bottom = top + (borderWidth + borderPadding) * 2 + height * cellDim;
	const int right = left + (borderWidth + borderPadding) * 2 + width * cellDim;

	// top
	gfx.DrawRect(left, top, right, top + borderWidth, borderColor);
	// left
	gfx.DrawRect(left, top + borderWidth, left + borderWidth, bottom - borderWidth, borderColor);
	// right
	gfx.DrawRect(right - borderWidth, top + borderWidth, right, bottom - borderWidth, borderColor);
	// bottom
	gfx.DrawRect(left, bottom - borderWidth, right, bottom, borderColor);
}

void Board::DrawScore(const int x, const int y, const int scoreWidth, const int scoreHeight, const Color c)
{
	const int left = x + topLeftX + borderWidth;
	const int top = y + topLeftY + borderWidth;
	gfx.DrawRectDim(left, top, scoreWidth, scoreHeight, c);
}

bool Board::CheckForObstacle(const Location & loc) const
{
	// Map 2D screen array to 1D hasObstacle array (Row Major) to get the correct array index
	//return hasObstacle[loc.y * width + loc.x]; 
	return boardCells[loc.y * width + loc.x] == 3; // 3 = Obstacle
}

bool Board::CheckForPoison(const Location & loc) const
{
	return boardCells[loc.y * width + loc.x] == 2; // 2 = Poison
}

void Board::AddObstacle(std::mt19937 & rng, const Snake & snake)
{
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);

	Location newLoc;
	do {
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);

	} while (CheckForObstacle(newLoc) || CheckForPoison(newLoc) || snake.IsInTile(newLoc));
	//} while (CheckForObstacle(newLoc) || snake.IsInTile(newLoc));

	// Map 2D screen array to 1D hasObstacle array (Row Major) to get the correct array index
	//hasObstacle[newLoc.y * width + newLoc.x] = true;
	boardCells[newLoc.y * width + newLoc.x] = 3; // 3 = Obstacle
}

void Board::EatPoison(const Location & loc)
{
	boardCells[loc.y * width + loc.x] = 0; // 0 = Empty
}

//void Board::DrawObstacles()
//{
//	for (int y = 0; y < height; y++)
//	{
//		for (int x = 0; x < width; x++)
//		{
//			if (CheckForObstacle({x, y}))
//			{
//				DrawCell({x, y}, obstacleColor);
//			}
//		}
//	}
//}
//
//void Board::DrawPoison()
//{
//	for (int y = 0; y < height; y++)
//	{
//		for (int x = 0; x < width; x++)
//		{
//			if (boardCells[y * width + x] == 2)
//			{
//				DrawCell({ x, y }, poisonColor);
//			}
//		}
//	}
//}

void Board::DrawBoard()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (boardCells[y * width + x] == 2) // Poison
			{
				DrawCell({ x, y }, poisonColor);
			}
			else if (boardCells[y * width + x] == 3) // Obstacle
			{
				DrawCell({ x, y }, obstacleColor);
			}
		}
	}
}

