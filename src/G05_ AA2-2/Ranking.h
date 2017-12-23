#pragma once
#include "Scene.h"
#include "Renderer.h"
#include "Types.h"
#include "Constants.h"
#include "Button.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


class Ranking : public Scene {

private:
	//variables
	Font font;
	Color color;
	Text scores;
	SDL_Rect scores_Rect;
	std::string BG_ID;
	SDL_Rect BG_Rect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	int scoresXpositionText;
	int scoresYpositionText;

public:
	Ranking();
	~Ranking();
	
	void EventHandler() override;
	void Update() override;
	void Draw() override;

	Button ButtonMenu;

};
