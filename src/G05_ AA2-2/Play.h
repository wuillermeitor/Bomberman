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
#include <fstream>

class Play : public Scene {

public:
	//variables
	std::string BG_ID;
	std::string ganador;
	int scoreganador;
	std::string ganadorRanking;
	SDL_Rect BG_Rect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	Player player1;
	Player player2;
	Key player1KeyMove;
	Key player2KeyMove;
	Level lvl;
	HUD hud;
	int lives;
	float time;
	bool findeljuego = false;
	//variable para la FINAL COUNTODOWN TIRORIO TIRORITOTI
	clock_t lastTime = clock();
	float deltaTime = 0;


	Play(std::string level);
	~Play();

	void EventHandler();
	void Update();
	void Draw();
};