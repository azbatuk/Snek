/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx),
	rng(std::random_device()()),
	snek({2 ,2})
{
	// Initialize Goals
	for (int i = 0; i < nGoals; i++)
	{
		brd.SpawnItem(rng, snek, Board::CellContents::Goal);
	}

	// Initialize Poisons
	for (int i = 0; i < nPoison; i++)
	{
		brd.SpawnItem(rng, snek, Board::CellContents::Poison);
	}

	sndTitle.Play(1.0f, 1.0f);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (gameIsStarted)
	{
		if (!gameIsOver)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				delta_loc = { 0, -1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				delta_loc = { 0, 1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				delta_loc = { -1, 0 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				delta_loc = { 1, 0 };
			}

			int snekModifiedMovePeriod = snekMovePeriod;
			if (wnd.kbd.KeyIsPressed(VK_CONTROL))
			{
				// Increase Snek's speed when Control key is pressed.
				// Snek will stop speeding up when key is released.

				/* 
				Using "min" to choose the smaller value, because eventually "snekMovePeriod" 
				can become a value less than "snekKeyPressedMovePeriod" at which time 
				pressing Control Key will actually slow down Snek if "snekKeyPressedMovePeriod"
				is simply assigned to "snekModifiedMovePeriod".
				*/
				snekModifiedMovePeriod = std::min(snekMovePeriod, snekKeyPressedMovePeriod);
			}

			// Update Snek at snekMovePeriod intervals to control its' speed.
			snekMoveCounter++;
			if (snekMoveCounter >= snekModifiedMovePeriod)
			{
				snekMoveCounter = 0;
				const Location nextLoc = snek.GetNextHeadLocation(delta_loc);
				if (!brd.IsInsideBoard(nextLoc) || snek.IsInTileExceptEnd(nextLoc) || brd.CheckForObstacle(nextLoc))
				{
					gameIsOver = true;
					sndGameOver.Play(rng, 1.1f);
					sndMusic.StopAll();
				}
				else
				{
					if (brd.CheckForPoison(nextLoc))
					{
						// eating poison
						brd.RemovePoison(nextLoc);
						sndRemovePoison.Play(rng, 0.6f);

						// increase Snek's speed by decreasing snekMovePeriod
						// at intervals determined by "poisonSpeedUpPeriod"
						poisonEatenCounter++;
						if (poisonEatenCounter >= poisonSpeedUpPeriod)
						{
							poisonEatenCounter = 0;
							snekMovePeriod = std::max(snekMovePeriod - 1, snekMovePeriodMin);
						}
					}

					const bool eating = brd.CheckForGoal(nextLoc);

					if (eating)
					{
						snek.Grow();
						brd.RemoveGoal(nextLoc);
					}
					snek.MoveBy(delta_loc);
					sfxSlither.Play(rng, 1.0f);
					if (eating)
					{
						brd.SpawnItem(rng, snek, Board::CellContents::Goal);
						brd.SpawnItem(rng, snek, Board::CellContents::Obstacle);
						score.AddScore();
						sfxEat.Play(rng, 0.8f);
					}
				}
			}
			// Increase Snek's speed at snekSpeedUpPeriod intervals
			snekSpeedUpCounter++;
			if (snekSpeedUpCounter >= snekSpeedUpPeriod)
			{
				snekSpeedUpCounter = 0;

				// std::max() returns bigger one of the two
				snekMovePeriod = std::max(snekMovePeriod - 1, snekMovePeriodMin);
			}
		}
	}
	else
	{
		gameIsStarted = wnd.kbd.KeyIsPressed(VK_RETURN);
		if (gameIsStarted)
		{
			sndMusic.Play(1.0f, 0.4f);
		}
	}
}

void Game::ComposeFrame()
{
	if (gameIsStarted)
	{
		brd.DrawBoard();
		snek.Draw(brd);
		score.Draw(brd);

		if (gameIsOver)
		{
			SpriteCodex::DrawGameOver(350, 265, gfx);
		}

		brd.DrawBorder();
	}
	else
	{
		SpriteCodex::DrawTitle(290, 225, gfx);
	}

	// Test Board drawing
	//std::uniform_int_distribution<int> colorDist(0, 255);
	//for (int y = 0; y < brd.GetGridHeight(); ++y)
	//{
	//	for (int x = 0; x < brd.GetGridWidth(); ++x)
	//	{
	//		Location loc = { x, y };
	//		Color c( colorDist(rng), colorDist(rng), colorDist(rng));
	//		brd.DrawCell(loc, c);
	//	}
	//}
}
