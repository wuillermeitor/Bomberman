#include "Button.h"

Button::Button()
{
	leftClick = false;
	font.id = "game_over";
	font.path = "../../res/ttf/game_over.ttf";
	font.size = 24;
	color = { 255, 0, 0, 0 };
	texto.color = color;
	texto.id = "texto_ID";
	texto.text = "Play";
	texto.h = 50;
	texto.w = 100;
	XpositionText = SCREEN_WIDTH / 2 - texto.w / 2;
	YpositionText = SCREEN_HEIGHT / 2 - texto.h / 2;
	Renderer::Instance()->LoadFont(font);
	Renderer::Instance()->LoadTextureText(font.id, texto);
	Texto_Rect = { XpositionText, YpositionText, texto.w, texto.h };
}


Button::~Button()
{
}

bool Button::isClicked()
{
	if (isHovered()) {
		if (leftClick) {
			return true;
		}
	}
	return false;
}

bool Button::isHovered()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x < (XpositionText + texto.w) && x >(XpositionText)) {
		if (y < (YpositionText + texto.h) && y >(YpositionText)) {
			return true;
		}
	}
	return false;
}

void Button::eventHandler(SDL_Event evento)
{
	switch (evento.type) {
	case SDL_MOUSEBUTTONDOWN:
		switch (evento.button.button) {
		case SDL_BUTTON_LEFT:
			leftClick = true;
			break;
		}
		break;
	default:
		leftClick = false;
	}

}

void Button::update()
{
	if (isClicked()) {
		std::cout << "click" << std::endl;

	}
	else if (isHovered())
		std::cout << "hover" << std::endl;


}

void Button::draw()
{
	Renderer::Instance()->PushImage(texto.id, Texto_Rect);
}
