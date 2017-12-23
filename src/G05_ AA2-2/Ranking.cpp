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
	//RANKING
	font.id = "game_over";
	font.path = "../../res/ttf/game_over.ttf";
	font.size = 500;
	color = { 0, 255, 255, 0 };
	scores.color = color;
	scores.text = "works?";
	scores.h = 100;
	scores.w = 200;
	scoresXpositionText = SCREEN_WIDTH / 2 - scores.w / 2;
	scoresYpositionText = SCREEN_HEIGHT / 2 - scores.h / 2;
	Renderer::Instance()->LoadFont(font);
	scores_Rect = { scoresXpositionText, scoresYpositionText, scores.w, scores.h };

	std::vector<std::pair<int, std::string>> ranking;
	std::string playerName;
	int score;
	std::ifstream fentrada("../../res/files/Ranking.bin", std::ios::binary);
	if (!fentrada.is_open()) {
		throw "error";
	}
	while (!fentrada.eof()) {
		fentrada >> playerName >> score;
		ranking.push_back({ score,playerName });
	}
	std::sort(ranking.rbegin(), ranking.rend());

	for (const auto &p : ranking) {
		std::cout << p.first << p.second << std::endl;
	}

	scores.text = ranking[0].second + ' '+ std::to_string(ranking[0].first) ;
	//scores1.text = std::to_string(ranking[1].first) + ranking[1].second;


}


Ranking::~Ranking()
{
}

void Ranking::Update() {
	ButtonMenu.update();
	Renderer::Instance()->LoadTextureText(font.id, scores);

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
	Renderer::Instance()->PushImage(scores.id, scores_Rect);
	ButtonMenu.draw();
	Renderer::Instance()->Render();
	Renderer::Instance()->Clear();
}