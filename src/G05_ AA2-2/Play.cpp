#pragma once
#include "Play.h"


Play::Play(std::string level) {
	scenestate = SceneState::RUNNING;
	BG_ID = BACKGROUND;
	std::string BGPath = "../../res/img/bgGame.jpg";
	Renderer::Instance()->LoadTexture(BG_ID, BGPath);
	if (level == "PLAY1") {
		lvl = Level();
	}
	else if (level == "PLAY2") {
		lvl = Level();
		std::cout << "He entrado en el nivel 2" << std::endl;
		Renderer::Instance()->LoadTexture(BACKGROUND, "../../res/img/bgGame.jpg");
		for (int i = 0; i < lvl.casillasAncho; i++) {
			lvl.tablero[i] = new casillas[lvl.casillasAlto];
			for (int j = 0; j < lvl.casillasAlto; j++) {
				if ((j == 0) && (i == 0) || (j == 1) && (i == 0) || (j == 0) && (i == 1) || (j == 12) && (i == 10) || (j == 11) && (i == 10) || (j == 12) && (i == 9)) {
					lvl.tablero[i][j] = casillas::EMPTY;
					//std::cout << "Casillas vacias" << std::endl;
				}
				else if (((j == 0) && (i == 10) || (j == 0) && (i == 9) || (j == 1) && (i == 10) || (j == 11) && (i == 0) || (j == 12) && (i == 0) || (j == 12) && (i == 1))) {
					lvl.tablero[i][j] = casillas::EMPTY;
					//std::cout << "Casillas vacias" << std::endl;
				}
				else if ((i == 1 || i == 3 || i == 5 || i == 7 || i == 9) && (j == 1 || j == 3 || j == 5 || j == 7 || j == 9 || j == 11)) {
					lvl.tablero[i][j] = casillas::INDESTRUCTIBLE_WALL;
				}
				else {
					lvl.auxrandomblock = (std::rand() % (2));
					std::cout << lvl.auxrandomblock << std::endl;
					if (lvl.auxrandomblock == 1)
						lvl.tablero[i][j] = casillas::DESTRUCTIBLE_WALL;
				}
			}
		}
	}
	lvl.limiteIJ = { 0, 0 };
	lvl.limiteWH = { lvl.casillasAncho, lvl.casillasAlto };

	//Load player 1
	player1 = Player();
	player1.Player_ID = PLAYER1_SPRITE;
	player1.PlayerPath = "../../res/img/player1.png";
	Renderer::Instance()->LoadTexture(player1.Player_ID, player1.PlayerPath);
	Renderer::Instance()->GetTextureSize(player1.Player_ID);
	player1.frameWidth = player1.textWidth / 3;
	player1.frameHeight = player1.textHeight / 4;
	player1.tmpPlayerPosition = lvl.CasillaACoordenada(0, 0);
	player1.Player_Position.x = player1.tmpPlayerPosition.x;
	player1.Player_Position.y = player1.tmpPlayerPosition.y;
	player1.Player_Rect.x = 0;
	player1.Player_Rect.y = 0;
	player1.Player_Position.h = LADO_CASILLA;
	player1.Player_Rect.h = LADO_CASILLA;
	player1.Player_Position.w = LADO_CASILLA;
	player1.Player_Rect.w = LADO_CASILLA;
	player1.frameTime = 0;
	player1.lifes = 3;
	player1.score = 0;

	//Load player 2
	player2 = Player();
	player2.Player_ID = PLAYER2_SPRITE;
	player2.PlayerPath = "../../res/img/player2.png";
	Renderer::Instance()->LoadTexture(player2.Player_ID, player2.PlayerPath);
	Renderer::Instance()->GetTextureSize(player2.Player_ID);
	player2.frameWidth = player2.textWidth / 3;
	player2.frameHeight = player2.textHeight / 4;
	player2.tmpPlayerPosition = lvl.CasillaACoordenada(lvl.casillasAncho - 1, 0);
	player2.Player_Position.x = player2.tmpPlayerPosition.x;
	player2.Player_Position.y = player2.tmpPlayerPosition.y;
	player2.Player_Rect.x = 0;
	player2.Player_Rect.y = 0;
	player2.Player_Position.h = LADO_CASILLA;
	player2.Player_Rect.h = LADO_CASILLA;
	player2.Player_Position.w = LADO_CASILLA;
	player2.Player_Rect.w = LADO_CASILLA;
	player2.frameTime = 0;
	player2.lifes = 3;
	player2.score = 0;

	//if (level == "PLAY1") {
	//	player1.lvl = lvl1;
	//	player2.lvl = lvl1;
	//}
	//else if (level == "PLAY2") {
	//	player1.lvl = lvl2;
	//	player2.lvl = lvl2;
	//}

	//HUD
	hud = HUD();
	hud.font.id = "game_over";
	hud.font.path = "../../res/ttf/game_over.ttf";
	hud.font.size = 100;
	hud.color = { 0, 0, 0, 0 };
	Renderer::Instance()->LoadFont(hud.font);
	//P1lifes
	hud.P1lifes.color = hud.color;
	hud.P1lifes.id = "texto1_ID";
	hud.P1lifes.text = "Lifes p1:  " + std::to_string(player1.lifes);
	hud.P1lifes.h = 50;
	hud.P1lifes.w = 80;
	hud.P1lifesXpositionText = 25;
	hud.P1lifesYpositionText = -10;
	Renderer::Instance()->LoadTextureText(hud.font.id, hud.P1lifes);
	hud.P1lifes_Rect = { hud.P1lifesXpositionText, hud.P1lifesYpositionText, hud.P1lifes.w, hud.P1lifes.h };
	//P2lifes
	hud.P2lifes.color = hud.color;
	hud.P2lifes.id = "texto2_ID";
	hud.P2lifes.text = "Lifes p2:  " + std::to_string(player2.lifes);
	hud.P2lifes.h = 50;
	hud.P2lifes.w = 80;
	hud.P2lifesXpositionText = 620;
	hud.P2lifesYpositionText = -10;
	Renderer::Instance()->LoadTextureText(hud.font.id, hud.P2lifes);
	hud.P2lifes_Rect = { hud.P2lifesXpositionText, hud.P2lifesYpositionText, hud.P2lifes.w, hud.P2lifes.h };

	//P1score
	hud.P1score.color = hud.color;
	hud.P1score.id = "texto3_ID";
	hud.P1score.text = "Score p1:  " + std::to_string(player1.score);
	hud.P1score.h = 50;
	hud.P1score.w = 80;
	hud.P1scoreXpositionText = 25;
	hud.P1scoreYpositionText = 30;
	Renderer::Instance()->LoadTextureText(hud.font.id, hud.P1score);
	hud.P1score_Rect = { hud.P1scoreXpositionText, hud.P1scoreYpositionText, hud.P1score.w, hud.P1score.h };
	//P2score
	hud.P2score.color = hud.color;
	hud.P2score.id = "texto4_ID";
	hud.P2score.text = "Score p2:  " + std::to_string(player2.score);
	hud.P2score.h = 50;
	hud.P2score.w = 80;
	hud.P2scoreXpositionText = 620;
	hud.P2scoreYpositionText = 30;
	Renderer::Instance()->LoadTextureText(hud.font.id, hud.P2score);
	hud.P2score_Rect = { hud.P2scoreXpositionText, hud.P2scoreYpositionText, hud.P2score.w, hud.P2score.h };
	//TIME
	hud.Time.color = hud.color;
	hud.Time.id = "texto5_ID";
	hud.Time.text = "Time left:  " + (std::to_string(hud.timeDown));
	hud.Time.h = 100;
	hud.Time.w = 300;
	hud.TimeXpositionText = 200;
	hud.TimeYpositionText = -15;
	Renderer::Instance()->LoadTextureText(hud.font.id, hud.Time);
	hud.Time_Rect = { hud.TimeXpositionText, hud.TimeYpositionText, hud.Time.w, hud.Time.h };
}


Play::~Play() {

}


void Play::EventHandler() {
	SDL_Event evento;
	while (SDL_PollEvent(&evento)) {
		if (hud.findeljuego || player1.lifes == 0 || player2.lifes == 0) {
			scenestate = SceneState::GOTOMENU;
		}
	}
}


void Play::Update() {
	const Uint8 *keyboardstate = SDL_GetKeyboardState(NULL);
	player1Position = player1.Movement(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE);
	player1.tmpPlayerPosition = lvl.CoordenadaACasilla(player1.Player_Position.x + LADO_CASILLA / 2, player1.Player_Position.y);
	std::cout << player1.Player_ID << " se encuentra en la posicion " << player1.tmpPlayerPosition.x << " " << player1.tmpPlayerPosition.y << std::endl;

	if (player1Position == Key::UP && player1.tmpPlayerPosition.y > lvl.limiteIJ.y) {
		std::cout << "UP" << std::endl;
		if (lvl.tablero[player1.tmpPlayerPosition.x][player1.tmpPlayerPosition.y - 1] == casillas::EMPTY) {
			player1.Player_Rect.y = 0;
			player1.Player_Position.y -= 5;
		}
	}
	else if (player1Position == Key::DOWN && player1.tmpPlayerPosition.y < lvl.limiteWH.y) {
		std::cout << "DOWN" << std::endl;
		if (lvl.tablero[player1.tmpPlayerPosition.x][player1.tmpPlayerPosition.y + 1] == casillas::EMPTY) {
			player1.Player_Rect.y = player1.Player_Rect.h * 2;
			player1.Player_Position.y += 5;
		}
	}
	else if (player1Position == Key::LEFT && player1.tmpPlayerPosition.x > lvl.limiteIJ.x) {
		std::cout << "LEFT" << std::endl;
		if (lvl.tablero[player1.tmpPlayerPosition.x - 1][player1.tmpPlayerPosition.y] == casillas::EMPTY) {
			player1.Player_Rect.y = player1.Player_Rect.h;
			player1.Player_Position.x -= 5;
		}
	}
	else if (player1Position == Key::RIGHT && player1.tmpPlayerPosition.x < lvl.limiteWH.x) {
		std::cout << "RIGHT" << std::endl;
		if (lvl.tablero[player1.tmpPlayerPosition.x + 1][player1.tmpPlayerPosition.y] == casillas::EMPTY) {
			player1.Player_Rect.y = player1.Player_Rect.h * 3;
			player1.Player_Position.x += 5;
		}
	}

	player2Position = player2.Movement(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_RCTRL);
	player2.tmpPlayerPosition = lvl.CoordenadaACasilla(player2.Player_Position.x, player2.Player_Position.y);
	std::cout << player2.Player_ID << " se encuentra en la posicion " << player2.tmpPlayerPosition.x << " " << player2.tmpPlayerPosition.y << std::endl;

	if (player2Position == Key::UP && player2.tmpPlayerPosition.y > lvl.limiteIJ.y) {
		std::cout << "UP" << std::endl;
		if (lvl.tablero[player2.tmpPlayerPosition.x][player2.tmpPlayerPosition.y - 1] == casillas::EMPTY) {
			player2.Player_Rect.y = 0;
			player2.Player_Position.y -= 5;
		}
	}
	else if (player2Position == Key::DOWN && player2.tmpPlayerPosition.y < lvl.limiteWH.y) {
		std::cout << "DOWN" << std::endl;
		if (lvl.tablero[player2.tmpPlayerPosition.x][player2.tmpPlayerPosition.y + 1] == casillas::EMPTY) {
			player2.Player_Rect.y = player2.Player_Rect.h * 2;
			player2.Player_Position.y += 5;
		}
	}
	else if (player2Position == Key::LEFT && player2.tmpPlayerPosition.x > lvl.limiteIJ.x) {
		std::cout << "LEFT" << std::endl;
		if (lvl.tablero[player2.tmpPlayerPosition.x - 1][player2.tmpPlayerPosition.y] == casillas::EMPTY) {
			player2.Player_Rect.y = player2.Player_Rect.h;
			player2.Player_Position.x -= 5;
		}
	}
	else if (player2Position == Key::RIGHT && player2.tmpPlayerPosition.x < lvl.limiteWH.x) {
		std::cout << "RIGHT" << std::endl;
		if (lvl.tablero[player2.tmpPlayerPosition.x + 1][player2.tmpPlayerPosition.y] == casillas::EMPTY) {
			player2.Player_Rect.y = player2.Player_Rect.h * 3;
			player2.Player_Position.x += 5;
		}
	}


	hud.Update();

}

void Play::Draw() {
	Renderer::Instance()->PushImage(BG_ID, BG_Rect);
	lvl.Draw();
	player1.Draw();
	player2.Draw();
	hud.Draw();
	Renderer::Instance()->Render();
	Renderer::Instance()->Clear();
}