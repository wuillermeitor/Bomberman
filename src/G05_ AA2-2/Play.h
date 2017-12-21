#pragma once
#include <iostream>
#include <string>
#include "Scene.h"
#include "Renderer.h"
#include "Types.h"
#include "Constants.h"
#include "Button.h"
#include "Player.h"
#include "Level.h"
#include "HUD.h"

class Play : public Scene {

public:
	//variables
	std::string BG_ID;
	SDL_Rect BG_Rect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	Player player1;
	Player player2;
	Key player1Position;
	Key player2Position;
	Level lvl;
	HUD hud;
	int lives;
	int time;


	Play(std::string level);
	~Play();

	void EventHandler();
	void Update();
	void Draw();
};