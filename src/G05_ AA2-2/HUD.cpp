#include "HUD.h"



HUD::HUD()
{
	font.id = "game_over";
	font.path = "../../res/ttf/game_over.ttf";
	font.size = 24;
	color = { 0, 255, 255, 0 };
	//P1lifes
	P1lifes.color = color;
	P1lifes.text = "works?";
	P1lifes.h = 50;
	P1lifes.w = 100;
	P1lifesXpositionText = SCREEN_WIDTH / 2 - P1lifes.w / 2;
	P1lifesYpositionText = SCREEN_HEIGHT / 2 - P1lifes.h / 2;
	Renderer::Instance()->LoadFont(font);
	P1lifes_Rect = { P1lifesXpositionText, P1lifesYpositionText, P1lifes.w, P1lifes.h };
	//P2lifes
	P2lifes.color = color;
	P2lifes.text = "works?";
	P2lifes.h = 50;
	P2lifes.w = 100;
	P2lifesXpositionText = SCREEN_WIDTH / 2 - P2lifes.w / 2;
	P2lifesYpositionText = SCREEN_HEIGHT / 2 - P2lifes.h / 2;
	P2lifes_Rect = { P2lifesXpositionText, P2lifesYpositionText, P2lifes.w, P2lifes.h };

	//P1score
	P1score.color = color;
	P1score.text = "works?";
	P1score.h = 50;
	P1score.w = 100;
	P1scoreXpositionText = SCREEN_WIDTH / 2 - P1score.w / 2;
	P1scoreYpositionText = SCREEN_HEIGHT / 2 - P1score.h / 2;
	P1score_Rect = { P1scoreXpositionText, P1scoreYpositionText, P1score.w, P1score.h };
	//P2score
	P2score.color = color;
	P2score.text = "works?";
	P2score.h = 50;
	P2score.w = 100;
	P2scoreXpositionText = SCREEN_WIDTH / 2 - P2score.w / 2;
	P2scoreYpositionText = SCREEN_HEIGHT / 2 - P2score.h / 2;
	P2score_Rect = { P2scoreXpositionText, P2scoreYpositionText, P2score.w, P2score.h };
	//Time
	Time.color = color;
	Time.text = "works?";
	Time.h = 50;
	Time.w = 100;
	TimeXpositionText = SCREEN_WIDTH / 2 - Time.w / 2;
	TimeYpositionText = SCREEN_HEIGHT / 2 - Time.h / 2;
	P2score_Rect = { TimeXpositionText, TimeYpositionText, Time.w, Time.h };
}


HUD::~HUD()
{

}

void HUD::Update() {
	Renderer::Instance()->LoadTextureText(font.id, Time);
	Renderer::Instance()->LoadTextureText(font.id, P1lifes);
	Renderer::Instance()->LoadTextureText(font.id, P1score);
	Renderer::Instance()->LoadTextureText(font.id, P2lifes);
	Renderer::Instance()->LoadTextureText(font.id, P2score);
	if (timeDown > 0) {
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime;
		//std::cout << timeDown << std::endl;
		Time.text = "Time left:  " + (std::to_string(static_cast<int>(timeDown)));
	}
	if (timeDown <= 0) {
		//std::cout << "FIN DEL JUEGO" << std::endl;
		Time.text = "FIN DEL JUEGO";
		findeljuego = true;
	}
}

void HUD::Draw() {
	Renderer::Instance()->PushImage(P1lifes.id, P1lifes_Rect);
	Renderer::Instance()->PushImage(P2lifes.id, P2lifes_Rect);
	Renderer::Instance()->PushImage(P1score.id, P1score_Rect);
	Renderer::Instance()->PushImage(P2score.id, P2score_Rect);
	Renderer::Instance()->PushImage(Time.id, Time_Rect);
}