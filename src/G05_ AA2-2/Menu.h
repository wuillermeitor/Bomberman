#pragma once
#include <iostream>
#include <string>
#include "Scene.h"
#include "Renderer.h"
#include "Types.h"
#include "Constants.h"
#include "Button.h"
#include "Ranking.h"
#include <SDL_mixer.h>
#include "Play.h"



class Menu : public Scene {

private:
	//variables
	std::string BG_ID;
	SDL_Rect BG_Rect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	bool audio = true;

public:
	Menu();
	~Menu();

	void EventHandler() override;
	void Update() override;
	void Draw() override;
	bool GetAudio();

	Button ButtonPlayLvl1;
	Button ButtonPlayLvl2;
	Button ButtonRanking;
	Button ButtonExit;
	Button ButtonMute;

};