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
	Text scores1;
	SDL_Rect scores1_Rect;
	Text scores2;
	SDL_Rect scores2_Rect;
	Text scores3;
	SDL_Rect scores3_Rect;
	Text scores4;
	SDL_Rect scores4_Rect;
	Text scores5;
	SDL_Rect scores5_Rect;
	Text scores6;
	SDL_Rect scores6_Rect;
	Text scores7;
	SDL_Rect scores7_Rect;
	Text scores8;
	SDL_Rect scores8_Rect;
	Text scores9;
	SDL_Rect scores9_Rect;
	std::string BG_ID;
	SDL_Rect BG_Rect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	int scoresXpositionText;
	int scoresYpositionText;
	int scores1XpositionText;
	int scores1YpositionText;
	int scores2XpositionText;
	int scores2YpositionText;
	int scores3XpositionText;
	int scores3YpositionText;
	int scores4XpositionText;
	int scores4YpositionText;
	int scores5XpositionText;
	int scores5YpositionText;
	int scores6XpositionText;
	int scores6YpositionText;
	int scores7XpositionText;
	int scores7YpositionText;
	int scores8XpositionText;
	int scores8YpositionText;
	int scores9XpositionText;
	int scores9YpositionText;

public:
	Ranking();
	~Ranking();

	void EventHandler() override;
	void Update() override;
	void Draw() override;

	Button ButtonMenu;

};
