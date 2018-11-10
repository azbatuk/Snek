#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>
class Board
{
public:
	enum class CellContents
	{
		Empty,
		Goal,
		Obstacle,
		Poison
	};
public:
	Board(Graphics& in_gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	void DrawBorder();
	void DrawScore(const int x, const int y, const int scoreWidht, const int scoreHeight, const Color c);
	bool CheckForGoal(const Location& loc) const;
	bool CheckForPoison(const Location& loc) const;
	bool CheckForObstacle(const Location& loc) const;
	void RemoveGoal(const Location& loc);
	void RemovePoison(const Location& loc);
	void SpawnItem(std::mt19937 & rng, const class Snake & snake, CellContents cellType);
	void DrawBoard();
private:
	static constexpr int cellDim = 20;		// Pixels
	static constexpr int cellPadding = 1;	// Pixels
	static constexpr int width = 32;		// Blocks
	static constexpr int height = 24;		// Blocks
	static constexpr int borderWidth = 4;	// Pixels
	static constexpr int borderPadding = 2;	// Pixels
	static constexpr int topLeftX = 70;		// Pixels
	static constexpr int topLeftY = 50;		// Pixels
	static constexpr Color borderColor = Colors::Blue;
	static constexpr Color goalColor = Colors::Red;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr Color poisonColor = Color(58, 0, 58);
	CellContents boardCells[width * height] = { CellContents::Empty };
	Graphics& gfx;
};