#include "Board.h"
#include <assert.h>

/*
Snake class is Forward Declared in Board.h to avoid 
circular dependency since Snake.h is including Board.h
As a result, Snake.h is being included here instead of in Board.h
*/
#include "Snake.h"

Board::Board(Graphics& in_gfx)
	:
	gfx(in_gfx)
{
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

Board::CellContents Board::GetCellContent(const Location & loc)
{
	// Map 2D screen array to 1D boardCells array (Row Major) to get the correct array index
	return boardCells[loc.y * width + loc.x];
}

bool Board::CheckForGoal(const Location & loc) const
{
	return boardCells[loc.y * width + loc.x] == CellContents::Goal;
}

bool Board::CheckForPoison(const Location & loc) const
{
	return boardCells[loc.y * width + loc.x] == CellContents::Poison;
}

bool Board::CheckForObstacle(const Location & loc) const
{
	return boardCells[loc.y * width + loc.x] == CellContents::Obstacle;
}

void Board::RemoveGoal(const Location & loc)
{
	boardCells[loc.y * width + loc.x] = CellContents::Empty;
}

void Board::RemovePoison(const Location & loc)
{
	boardCells[loc.y * width + loc.x] = CellContents::Empty;
}

void Board::SpawnItem(std::mt19937 & rng, const Snake & snake, CellContents cellType)
{
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);

	Location newLoc;
	do {
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc) || boardCells[newLoc.y * width + newLoc.x] != CellContents::Empty);

	boardCells[newLoc.y * width + newLoc.x] = cellType;
}

void Board::DrawBoard()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			const CellContents cellContent = GetCellContent( {x, y} );

			switch (cellContent)
			{
			case CellContents::Goal:
				DrawCell({ x, y }, goalColor);
				break;
			case CellContents::Poison:
				DrawCell({ x, y }, poisonColor);
				break;
			case CellContents::Obstacle:
				DrawCell({ x, y }, obstacleColor);
				break;
			}
		}
	}
}

