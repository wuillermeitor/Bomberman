#pragma once
#include "Menu.h"



Menu::Menu()
{
	scenestate = SceneState::RUNNING;
	BG_ID = BACKGROUND;
	std::string BGPath = "../../res/img/bgGame.jpg";
	Renderer::Instance()->LoadTexture(BG_ID, BGPath);

	//Music
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags) & mixFlags))throw"Error:SDL_mixer init";
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw "Unable o initialize SDL_mixer audio systems";
	}
	Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/menu.mp3") };
	if (!soundtrack) throw "Unable to load the Mix_Music soundtrack";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soundtrack, -1);
	audio = true;

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
	ButtonRanking.texto.h = 70;
	ButtonRanking.texto.w = 120;
	ButtonRanking.XpositionText = SCREEN_WIDTH / 2 - ButtonRanking.texto.w / 2;
	ButtonRanking.YpositionText = (SCREEN_HEIGHT / 2) + 75;
	Renderer::Instance()->LoadFont(ButtonRanking.font);
	Renderer::Instance()->LoadTextureText(ButtonRanking.font.id, ButtonRanking.texto);
	ButtonRanking.Texto_Rect = { ButtonRanking.XpositionText, ButtonRanking.YpositionText, ButtonRanking.texto.w, ButtonRanking.texto.h };

	//Button Mute
	ButtonMute = Button();
	ButtonMute.font.id = "game_over";
	ButtonMute.font.path = "../../res/ttf/game_over.ttf";
	ButtonMute.font.size = 50;
	ButtonMute.color = { 255, 0, 0, 0 };
	ButtonMute.texto.color = ButtonMute.color;
	ButtonMute.texto.id = "texto4_ID";
	ButtonMute.texto.text = "Desactivar so";
	ButtonMute.texto.h = 70;
	ButtonMute.texto.w = 170;
	ButtonMute.XpositionText = SCREEN_WIDTH / 2 - ButtonMute.texto.w / 2;
	ButtonMute.YpositionText = (SCREEN_HEIGHT / 2) + 125;
	Renderer::Instance()->LoadFont(ButtonMute.font);
	Renderer::Instance()->LoadTextureText(ButtonMute.font.id, ButtonMute.texto);
	ButtonMute.Texto_Rect = { ButtonMute.XpositionText, ButtonMute.YpositionText, ButtonMute.texto.w, ButtonMute.texto.h };

	//Button Exit
	ButtonExit = Button();
	ButtonExit.font.id = "game_over";
	ButtonExit.font.path = "../../res/ttf/game_over.ttf";
	ButtonExit.font.size = 50;
	ButtonExit.color = { 255, 0, 0, 0 };
	ButtonExit.texto.color = ButtonExit.color;
	ButtonExit.texto.id = "texto5_ID";
	ButtonExit.texto.text = "Sortir";
	ButtonExit.texto.h = 70;
	ButtonExit.texto.w = 100;
	ButtonExit.XpositionText = SCREEN_WIDTH / 2 - ButtonExit.texto.w / 2;
	ButtonExit.YpositionText = (SCREEN_HEIGHT / 2) + 175;
	Renderer::Instance()->LoadFont(ButtonExit.font);
	Renderer::Instance()->LoadTextureText(ButtonExit.font.id, ButtonExit.texto);
	ButtonExit.Texto_Rect = { ButtonExit.XpositionText, ButtonExit.YpositionText, ButtonExit.texto.w, ButtonExit.texto.h };
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
		ButtonMute.eventHandler(evento);
		ButtonExit.eventHandler(evento);
		if (ButtonPlayLvl1.isClicked()) {
			scenestate = SceneState::GOTOLVL1;
		}
		if (ButtonPlayLvl2.isClicked()) {
			scenestate = SceneState::GOTOLVL2;
		}
		else if (ButtonRanking.isClicked()) {
			scenestate = SceneState::GOTORANKING;
		}
		else if (ButtonMute.isClicked()) {
			if (audio == true) {
				Mix_PauseMusic();
				audio = false;
			}
			else {
				Mix_ResumeMusic();
				audio = true;
			}
		}
		else if (ButtonExit.isClicked()) {
			exit(0);
		}
	}
}

void Menu::Update() {
	ButtonPlayLvl1.update();
	ButtonPlayLvl2.update();
	ButtonRanking.update();
	ButtonMute.update();
	ButtonExit.update();
}

void Menu::Draw() {
	Renderer::Instance()->PushImage(BG_ID, BG_Rect);
	ButtonPlayLvl1.draw();
	ButtonPlayLvl2.draw();
	ButtonRanking.draw();
	ButtonMute.draw();
	ButtonExit.draw();
	Renderer::Instance()->Render();
	Renderer::Instance()->Clear();
}

bool Menu::GetAudio() {
	return audio;
}
