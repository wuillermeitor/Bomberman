#pragma once
#include "Ranking.h"



Ranking::Ranking()
{
	scenestate = SceneState::RUNNING;
	BG_ID = BACKGROUND;
	std::string BGPath = "../../res/img/bgGame.jpg";
	Renderer::Instance()->LoadTexture(BG_ID, BGPath);
	ButtonMenu = Button();
	ButtonMenu.font.id = "game_over";
	ButtonMenu.font.path = "../../res/ttf/game_over.ttf";
	ButtonMenu.font.size = 24;
	ButtonMenu.color = { 255, 0, 0, 0 };
	ButtonMenu.texto.color = ButtonMenu.color;
	ButtonMenu.texto.id = "texto3_ID";
	ButtonMenu.texto.text = "Menu";
	ButtonMenu.texto.h = 50;
	ButtonMenu.texto.w = 100;
	ButtonMenu.XpositionText = SCREEN_WIDTH / 2 - ButtonMenu.texto.w / 2;
	ButtonMenu.YpositionText = 600;
	Renderer::Instance()->LoadFont(ButtonMenu.font);
	Renderer::Instance()->LoadTextureText(ButtonMenu.font.id, ButtonMenu.texto);
	ButtonMenu.Texto_Rect = { ButtonMenu.XpositionText, ButtonMenu.YpositionText, ButtonMenu.texto.w, ButtonMenu.texto.h };
}


Ranking::~Ranking()
{
}

void Ranking::Update() {
	ButtonMenu.update();
}


void Ranking::EventHandler() {
	SDL_Event evento;
	while (SDL_PollEvent(&evento)) {
		ButtonMenu.eventHandler(evento);
		ButtonMenu.eventHandler(evento);
		if (ButtonMenu.isClicked()) {
			scenestate = SceneState::GOTOMENU;
		}
	}
}

void Ranking::Draw() {
	Renderer::Instance()->PushImage(BG_ID, BG_Rect);
	ButtonMenu.draw();
	Renderer::Instance()->Render();
	Renderer::Instance()->Clear();
}