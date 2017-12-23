#pragma once
#include <string>
#include "Renderer.h"

class GameObject
{
public:
	std::string GameObject_ID, GameObjectPath;
	SDL_Rect GameObject_Rect, GameObject_Position;
	int frameWidth, frameHeight;
	int textWidth = 144;
	int textHeight = 96;
	GameObject();
	~GameObject();

	void draw(std::string GameObject_ID, int i, int j);
};

