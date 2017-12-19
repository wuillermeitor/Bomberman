#pragma once
#include <string>
#include "Renderer.h"

class Wall
{
public:
	std::string Wall_ID, WallPath;
	SDL_Rect Wall_Rect, Wall_Position;
	int frameWidth, frameHeight;
	int textWidth = 144;
	int textHeight = 96;
	float probability_PU = 20;
	Wall();
	~Wall();

	void setup();
	void draw(std::string wall_ID, int i, int j);
	void update();
};