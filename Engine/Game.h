/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include "Score.h"
#include "SoundEffect.h"
#include <random>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Board brd;
	Snake snek;
	Location delta_loc = { 1, 0 }; // Initial move by Snek. x is increasing, so from left to right.
	std::mt19937 rng;
	Score score;
	SoundEffect sfxEat = SoundEffect({ L"Sounds\\Eat.wav" });
	SoundEffect sfxSlither = SoundEffect({ L"Sounds\\Slither0.wav",L"Sounds\\Slither1.wav",L"Sounds\\Slither2.wav" });
	Sound sndMusic = Sound(L"Sounds\\Music_Loop.wav", Sound::LoopType::AutoFullSound);
	Sound sndTitle = Sound(L"Sounds\\Title.wav");
	SoundEffect sndRemovePoison = SoundEffect({ L"Sounds\\EatPoison.wav" });
	SoundEffect sndGameOver = SoundEffect({ L"Sounds\\Fart.wav" });
	static constexpr int snekMovePeriodMin = 4; // Frames
	int snekMoveCounter = 0;
	int snekMovePeriod = 20; // Snek will move once every this many Frames. 
							 // It will decrease (to speed Snek up) at "snekSpeedUpPeriod" intervals and 
							 // also at every "poisonSpeedUpPeriod" number of poisons eaten.
	int snekSpeedUpCounter = 0;
	static constexpr int snekSpeedUpPeriod = 180; // Snek speed up interval: Frames (60 frames/second * 3 seconds = 180)
	int poisonEatenCounter = 0;
	static constexpr int poisonSpeedUpPeriod = 10; // No of poisons eaten that will speed Snek up
	static constexpr int snekKeyPressedMovePeriod = 5; // While Control Key is pressed: No of frames that will speed Snek up

	static constexpr int nGoals = 5;
	int nPoison = (brd.GetGridWidth() * brd.GetGridHeight()) / 3;

	bool gameIsOver = false;
	bool gameIsStarted = false;
	/********************************/
};