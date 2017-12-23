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
	scores.h = 50;
	scores.w = 200;
	scoresXpositionText = SCREEN_WIDTH / 2 - scores.w / 2;
	scoresYpositionText = 60;
	Renderer::Instance()->LoadFont(font);
	scores_Rect = { scoresXpositionText, scoresYpositionText, scores.w, scores.h };

	scores1.color = color;
	scores1.text = "works?";
	scores1.h = 50;
	scores1.w = 200;
	scores1XpositionText = SCREEN_WIDTH / 2 - scores1.w / 2;
	scores1YpositionText = 120;
	scores1_Rect = { scores1XpositionText, scores1YpositionText, scores1.w, scores1.h };

	scores2.color = color;
	scores2.text = "works?";
	scores2.h = 50;
	scores2.w = 200;
	scores2XpositionText = SCREEN_WIDTH / 2 - scores2.w / 2;
	scores2YpositionText = 180;
	scores2_Rect = { scores2XpositionText, scores2YpositionText, scores2.w, scores2.h };

	scores3.color = color;
	scores3.text = "works?";
	scores3.h = 50;
	scores3.w = 200;
	scores3XpositionText = SCREEN_WIDTH / 2 - scores3.w / 2;
	scores3YpositionText = 240;
	scores3_Rect = { scores3XpositionText, scores3YpositionText, scores3.w, scores3.h };

	scores4.color = color;
	scores4.text = "works?";
	scores4.h = 50;
	scores4.w = 200;
	scores4XpositionText = SCREEN_WIDTH / 2 - scores4.w / 2;
	scores4YpositionText = 300;
	scores4_Rect = { scores4XpositionText, scores4YpositionText, scores4.w, scores4.h };

	scores5.color = color;
	scores5.text = "works?";
	scores5.h = 50;
	scores5.w = 200;
	scores5XpositionText = SCREEN_WIDTH / 2 - scores5.w / 2;
	scores5YpositionText = 360;
	scores5_Rect = { scores5XpositionText, scores5YpositionText, scores5.w, scores5.h };

	scores6.color = color;
	scores6.text = "works?";
	scores6.h = 50;
	scores6.w = 200;
	scores6XpositionText = SCREEN_WIDTH / 2 - scores6.w / 2;
	scores6YpositionText = 420;
	scores6_Rect = { scores6XpositionText, scores6YpositionText, scores6.w, scores6.h };

	scores7.color = color;
	scores7.text = "works?";
	scores7.h = 50;
	scores7.w = 200;
	scores7XpositionText = SCREEN_WIDTH / 2 - scores7.w / 2;
	scores7YpositionText = 480;
	scores7_Rect = { scores7XpositionText, scores7YpositionText, scores7.w, scores7.h };

	scores8.color = color;
	scores8.text = "works?";
	scores8.h = 50;
	scores8.w = 200;
	scores8XpositionText = SCREEN_WIDTH / 2 - scores8.w / 2;
	scores8YpositionText = 540;
	scores8_Rect = { scores8XpositionText, scores8YpositionText, scores8.w, scores8.h };

	scores9.color = color;
	scores9.text = "works?";
	scores9.h = 50;
	scores9.w = 200;
	scores9XpositionText = SCREEN_WIDTH / 2 - scores9.w / 2;
	scores9YpositionText = 600;
	scores9_Rect = { scores9XpositionText, scores9YpositionText, scores9.w, scores9.h };

	std::vector<std::pair<int, std::string>> ranking;
	ranking.push_back({ -1," " });
	ranking.push_back({ -1," " });
	ranking.push_back({ -1," " });
	ranking.push_back({ -1," " });
	ranking.push_back({ -1," " });
	ranking.push_back({ -1," " });
	ranking.push_back({ -1," " });
	ranking.push_back({ -1," " });
	ranking.push_back({ -1," " });
	ranking.push_back({ -1," " });
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
		std::sort(ranking.rbegin(), ranking.rend());
	}
		scores.text = ranking[0].second + ' ' + std::to_string(ranking[0].first);
		scores1.text = ranking[1].second + ' ' + std::to_string(ranking[1].first);
		scores2.text = ranking[2].second + ' ' + std::to_string(ranking[2].first);
		scores3.text = ranking[3].second + ' ' + std::to_string(ranking[3].first);
		scores4.text = ranking[4].second + ' ' + std::to_string(ranking[4].first);
		scores5.text = ranking[5].second + ' ' + std::to_string(ranking[5].first);
		scores6.text = ranking[6].second + ' ' + std::to_string(ranking[6].first);
		scores7.text = ranking[7].second + ' ' + std::to_string(ranking[7].first);
		scores8.text = ranking[8].second + ' ' + std::to_string(ranking[8].first);
		scores9.text = ranking[9].second + ' ' + std::to_string(ranking[9].first);
	
	//scores1.text = std::to_string(ranking[1].first) + ranking[1].second;


}


Ranking::~Ranking()
{
}

void Ranking::Update() {
	ButtonMenu.update();
	Renderer::Instance()->LoadTextureText(font.id, scores);
	Renderer::Instance()->LoadTextureText(font.id, scores1);
	Renderer::Instance()->LoadTextureText(font.id, scores2);
	Renderer::Instance()->LoadTextureText(font.id, scores3);
	Renderer::Instance()->LoadTextureText(font.id, scores4);
	Renderer::Instance()->LoadTextureText(font.id, scores5);
	Renderer::Instance()->LoadTextureText(font.id, scores6);
	Renderer::Instance()->LoadTextureText(font.id, scores7);
	Renderer::Instance()->LoadTextureText(font.id, scores8);
	Renderer::Instance()->LoadTextureText(font.id, scores9);
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
	Renderer::Instance()->PushImage(scores1.id, scores1_Rect);
	Renderer::Instance()->PushImage(scores2.id, scores2_Rect);
	Renderer::Instance()->PushImage(scores3.id, scores3_Rect);
	Renderer::Instance()->PushImage(scores4.id, scores4_Rect);
	Renderer::Instance()->PushImage(scores5.id, scores5_Rect);
	Renderer::Instance()->PushImage(scores6.id, scores6_Rect);
	Renderer::Instance()->PushImage(scores7.id, scores7_Rect);
	Renderer::Instance()->PushImage(scores8.id, scores8_Rect);
	Renderer::Instance()->PushImage(scores9.id, scores9_Rect);
	ButtonMenu.draw();
	Renderer::Instance()->Render();
	Renderer::Instance()->Clear();
}