#pragma once
#include <iostream>
#include "Renderer.h"
#include "Types.h"

class Button {
public:
	Button();
	~Button();
	void eventHandler(SDL_Event buttonevent);
	bool isClicked();
	bool isHovered();
	void update();
	void draw();

	Font font;
	Text texto;
	Color color;
	SDL_Rect Texto_Rect;
	int XpositionText;
	int YpositionText;


private:
	bool leftClick;
};
