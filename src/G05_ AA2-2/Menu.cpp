#pragma once
#include "Menu.h"



Menu::Menu()
{
	scenestate = SceneState::RUNNING;
	BG_ID = BACKGROUND;
	std::string BGPath = "../../res/img/bgGame.jpg";
	Renderer::Instance()->LoadTexture(BG_ID, BGPath);

	//Button Play Level 1
	ButtonPlayLvl1 = Button();
	ButtonPlayLvl1.font.id = "game_over";
	ButtonPlayLvl1.font.path = "../../res/ttf/game_over.ttf";
	ButtonPlayLvl1.font.size = 50;
	ButtonPlayLvl1.color = { 255, 0, 0, 0 };
	ButtonPlayLvl1.texto.color = ButtonPlayLvl1.color;
	ButtonPlayLvl1.texto.id = "texto1_ID";
	ButtonPlayLvl1.texto.text = " Play Level 1";
	ButtonPlayLvl1.texto.h = 100;
	ButtonPlayLvl1.texto.w = 150;
	ButtonPlayLvl1.XpositionText = SCREEN_WIDTH / 2 - ButtonPlayLvl1.texto.w / 2;
	ButtonPlayLvl1.YpositionText = (SCREEN_HEIGHT / 2 - ButtonPlayLvl1.texto.h / 2) - 100;
	Renderer::Instance()->LoadFont(ButtonPlayLvl1.font);
	Renderer::Instance()->LoadTextureText(ButtonPlayLvl1.font.id, ButtonPlayLvl1.texto);
	ButtonPlayLvl1.Texto_Rect = { ButtonPlayLvl1.XpositionText, ButtonPlayLvl1.YpositionText, ButtonPlayLvl1.texto.w, ButtonPlayLvl1.texto.h };

	//Button Play Level 2
	ButtonPlayLvl2 = Button();
	ButtonPlayLvl2.font.id = "game_over";
	ButtonPlayLvl2.font.path = "../../res/ttf/game_over.ttf";
	ButtonPlayLvl2.font.size = 50;
	ButtonPlayLvl2.color = { 255, 0, 0, 0 };
	ButtonPlayLvl2.texto.color = ButtonPlayLvl2.color;
	ButtonPlayLvl2.texto.id = "texto2_ID";
	ButtonPlayLvl2.texto.text = " Play Level 2";
	ButtonPlayLvl2.texto.h = 100;
	ButtonPlayLvl2.texto.w = 150;
	ButtonPlayLvl2.XpositionText = SCREEN_WIDTH / 2 - ButtonPlayLvl2.texto.w / 2;
	ButtonPlayLvl2.YpositionText = (SCREEN_HEIGHT / 2 - ButtonPlayLvl2.texto.h / 2);
	Renderer::Instance()->LoadFont(ButtonPlayLvl2.font);
	Renderer::Instance()->LoadTextureText(ButtonPlayLvl2.font.id, ButtonPlayLvl2.texto);
	ButtonPlayLvl2.Texto_Rect = { ButtonPlayLvl2.XpositionText, ButtonPlayLvl2.YpositionText, ButtonPlayLvl2.texto.w, ButtonPlayLvl2.texto.h };

	//Bbutton Ranking
	ButtonRanking = Button();
	ButtonRanking.font.id = "game_over";
	ButtonRanking.font.path = "../../res/ttf/game_over.ttf";
	ButtonRanking.font.size = 50;
	ButtonRanking.color = { 255, 0, 0, 0 };
	ButtonRanking.texto.color = ButtonRanking.color;
	ButtonRanking.texto.id = "texto3_ID";
	ButtonRanking.texto.text = "Ranking";
	ButtonRanking.texto.h = 50;
	ButtonRanking.texto.w = 100;
	ButtonRanking.XpositionText = SCREEN_WIDTH / 2 - ButtonRanking.texto.w / 2;
	ButtonRanking.YpositionText = (SCREEN_HEIGHT / 2) + 100;
	Renderer::Instance()->LoadFont(ButtonRanking.font);
	Renderer::Instance()->LoadTextureText(ButtonRanking.font.id, ButtonRanking.texto);
	ButtonRanking.Texto_Rect = { ButtonRanking.XpositionText, ButtonRanking.YpositionText, ButtonRanking.texto.w, ButtonRanking.texto.h };
}


Menu::~Menu()
{
}

void Menu::EventHandler() {
	SDL_Event evento;
	while (SDL_PollEvent(&evento)) {
		ButtonPlayLvl1.eventHandler(evento);
		ButtonPlayLvl2.eventHandler(evento);
		ButtonRanking.eventHandler(evento);
		if (ButtonPlayLvl1.isClicked()) {
			scenestate = SceneState::GOTOLVL1;
		}
		if (ButtonPlayLvl2.isClicked()) {
			scenestate = SceneState::GOTOLVL2;
		}
		else if (ButtonRanking.isClicked()) {
			scenestate = SceneState::GOTORANKING;
		}
	}
}

void Menu::Update() {
	ButtonPlayLvl1.update();
	ButtonPlayLvl2.update();
	ButtonRanking.update();
}

void Menu::Draw() {
	Renderer::Instance()->PushImage(BG_ID, BG_Rect);
	ButtonPlayLvl1.draw();
	ButtonPlayLvl2.draw();
	ButtonRanking.draw();
	Renderer::Instance()->Render();
	Renderer::Instance()->Clear();
}