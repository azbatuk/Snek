#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>
class Board
{
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
	void AddGoal(const Location& loc);
	void RemoveGoal(const Location& loc);
	void RemovePoison(const Location& loc);
	void AddObstacle(std::mt19937 & rng, const class Snake & snake);
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
	bool hasObstacle[width * height] = { false };
	int boardCells[width * height] = { 0 }; // 0 = Empty, 1 = Goal, 2 = Poison, 3 = Obstacle
	int nGoals = 5;
	int nPoison = (width * height) / 3;
	Graphics& gfx;
};