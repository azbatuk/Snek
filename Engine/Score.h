#pragma once

#include "Board.h"

class Score
{
public:
	void Draw(Board& brd) const;
	void AddScore();
private:
	int score = 0;
	static constexpr int x = -2; // Pixel - negative value to place score outside the border
	static constexpr int y = -15; // Pixel - negative value to place score outside the border
	static constexpr int scoreWidth = 2;	// Pixel
	static constexpr int scoreHeight = 10;	// Pixel
	static constexpr int scorePadding = 3;	// Pixel
	static constexpr Color c = Colors::Magenta;
};