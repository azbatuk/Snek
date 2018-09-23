#include "Score.h"

void Score::Draw(Board & brd) const
{
	for (int i = 0; i < score; i++)
	{
		brd.DrawScore(x + (i * scorePadding), y, scoreWidth, scoreHeight, c);
	}
}

void Score::AddScore()
{
	score++;
}

