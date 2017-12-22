#pragma once
#include "Play.h"
#include "../../dep/inc/xml/rapidxml.hpp"
#include "../../dep/inc/xml/rapidxml_iterators.hpp"
#include "../../dep/inc/xml/rapidxml_print.hpp"
#include "../../dep/inc/xml/rapidxml_utils.hpp"
#include <sstream>

Play::Play(std::string level) {
	scenestate = SceneState::RUNNING;
	BG_ID = BACKGROUND;
	std::string BGPath = "../../res/img/bgGame.jpg";
	Renderer::Instance()->LoadTexture(BG_ID, BGPath);

	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);



	if (level == "PLAY1") {
		lvl = Level();
		std::cout << "He entrado en el nivel 1" << std::endl;
		std::cout << "Nombre de la raiz:" << doc.first_node()->name() << std::endl;

		rapidxml::xml_node<> *pRoot = doc.first_node();

		rapidxml::xml_node<> *pLevel = pRoot->first_node("Level");

		time = atoi(pLevel->first_attribute("time")->value());		//Segons que durara com a maxim la partida

		std::cout << time << std::endl;
		lives = atoi(pLevel->first_attribute("lives")->value());	//vides dels jugadors

		std::cout << lives << std::endl;


		/*	for (int i = 0; i <= lvl.casillasAncho; i++) {
		for (int j = 0; j <= lvl.casillasAlto; j++) {*/
		for (rapidxml::xml_node<> *pWall = pLevel->first_node("Destructible")->first_node("Wall"); pWall; pWall = pWall->next_sibling("Wall")) {

			int i = atoi(pWall->first_attribute("j")->value());
			int j = atoi(pWall->first_attribute("i")->value());

			lvl.tablero[i][j] = casillas::DESTRUCTIBLE_WALL;
			std::cout << "Creo bloque destruible en" << i << " " << j << std::endl;

		}


		for (rapidxml::xml_node<> *pWall = pLevel->first_node("Fixed")->first_node("Wall"); pWall; pWall = pWall->next_sibling("Wall")) {

			int i = atoi(pWall->first_attribute("j")->value());
			int j = atoi(pWall->first_attribute("i")->value());

			lvl.tablero[i][j] = casillas::INDESTRUCTIBLE_WALL;
			std::cout << "Creo bloque indestructible en" << i << " " << j << std::endl;

		}

		lvl.limiteIJ = { 0, 0 };
		lvl.limiteWH = { lvl.casillasAncho, lvl.casillasAlto };
		//	}
		//}
	}



	else if (level == "PLAY2") {
		std::cout << "Nombre de la raiz:" << doc.first_node()->name() << std::endl;

		rapidxml::xml_node<> *pRoot = doc.first_node();

		rapidxml::xml_node<> *pLevel = pRoot->first_node("Level");

		pLevel = pLevel->next_sibling("Level");



		time = atoi(pLevel->first_attribute("time")->value());		//Segons que durara com a maxim la partida
		std::cout << time << std::endl;
		lives = atoi(pLevel->first_attribute("lives")->value());	//vides dels jugadors
		std::cout << lives << std::endl;


		lvl = Level();
		std::cout << "He entrado en el nivel 2" << std::endl;
		Renderer::Instance()->LoadTexture(BACKGROUND, "../../res/img/bgGame.jpg");
		for (rapidxml::xml_node<> *pWall = pLevel->first_node("Destructible")->first_node("Wall"); pWall; pWall = pWall->next_sibling("Wall")) {

			int i = atoi(pWall->first_attribute("j")->value());
			int j = atoi(pWall->first_attribute("i")->value());

			lvl.tablero[i][j] = casillas::DESTRUCTIBLE_WALL;
			std::cout << "Creo bloque destruible en" << i << " " << j << std::endl;
		}


		for (rapidxml::xml_node<> *pWall = pLevel->first_node("Fixed")->first_node("Wall"); pWall; pWall = pWall->next_sibling("Wall")) {

			int i = atoi(pWall->first_attribute("j")->value());
			int j = atoi(pWall->first_attribute("i")->value());

			lvl.tablero[i][j] = casillas::INDESTRUCTIBLE_WALL;
			std::cout << "Creo bloque indestructible en" << i << " " << j << std::endl;
		}
		lvl.limiteIJ = { 0, 0 };
		lvl.limiteWH = { lvl.casillasAncho, lvl.casillasAlto };

	}


	//Load player 1
	player1 = Player();
	player1.Player_ID = PLAYER1_SPRITE;
	player1.PlayerPath = "../../res/img/player1.png";
	Renderer::Instance()->LoadTexture(player1.Player_ID, player1.PlayerPath);
	Renderer::Instance()->GetTextureSize(player1.Player_ID);
	player1.frameWidth = player1.textWidth / 3;
	player1.frameHeight = player1.textHeight / 4;
	player1.PlayerPositionXY = lvl.CasillaACoordenada(0, 0);
	player1.PlayerPositionWH.x = player1.PlayerPositionXY.x + LADO_CASILLA - 2;
	player1.PlayerPositionWH.y = player1.PlayerPositionXY.y + LADO_CASILLA - 2;
	player1.Player_Position.x = player1.PlayerPositionXY.x;
	player1.Player_Position.y = player1.PlayerPositionXY.y;
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
	player2.PlayerPositionXY = lvl.CasillaACoordenada(lvl.casillasAncho - 1, 0);
	player2.Player_Position.x = player2.PlayerPositionXY.x;
	player2.Player_Position.y = player2.PlayerPositionXY.y;
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
	player1KeyMove = player1.Movement(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE);
	player1.PlayerPositionXY = lvl.CoordenadaACasilla(player1.Player_Position.x, player1.Player_Position.y - (LADO_CASILLA + 17) / 2);
	player1.PlayerPositionWH = lvl.CoordenadaACasilla(player1.Player_Position.x + LADO_CASILLA - 2, player1.Player_Position.y - ((LADO_CASILLA + 17) / 2) + LADO_CASILLA - 2);
	//std::cout << player1.Player_ID << " se encuentra en la posicion x y " << player1.PlayerPositionXY.x << " " << player1.PlayerPositionXY.y << std::endl;
	//std::cout << player1.Player_ID << " se encuentra en la posicion w h " << player1.PlayerPositionWH.x << " " << player1.PlayerPositionWH.y << std::endl;
	if (player1KeyMove == Key::UP && player1.PlayerPositionXY.y >= lvl.limiteIJ.y && player1.Player_Position.x >= LADO_CASILLA) {
		if (lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y] == casillas::EMPTY && lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y] == casillas::EMPTY) {
			player1.Player_Rect.y = 0;
			player1.Player_Position.y -= 2;
		}
	}
	else if (player1KeyMove == Key::DOWN && player1.PlayerPositionXY.y + 1 < lvl.limiteWH.y && player1.Player_Position.x >= LADO_CASILLA) {
		if (lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y + 1] == casillas::EMPTY && lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y] == casillas::EMPTY) {
			player1.Player_Rect.y = player1.Player_Rect.h * 2;
			player1.Player_Position.y += 2;
		}
	}
	else if (player1KeyMove == Key::LEFT && player1.PlayerPositionXY.x >= lvl.limiteIJ.x && player1.Player_Position.y >= LADO_CASILLA + HUD_HEIGHT) {
		if (lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y] == casillas::EMPTY && lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y] == casillas::EMPTY) {
			player1.Player_Rect.y = player1.Player_Rect.h;
			player1.Player_Position.x -= 2;
		}
	}
	else if (player1KeyMove == Key::RIGHT && player1.PlayerPositionXY.x + 1 < lvl.limiteWH.x && player1.Player_Position.y >= LADO_CASILLA + HUD_HEIGHT) {
		if (lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y] == casillas::EMPTY && lvl.tablero[player1.PlayerPositionWH.x + 1][player1.PlayerPositionWH.y] == casillas::EMPTY) {
			player1.Player_Rect.y = player1.Player_Rect.h * 3;
			player1.Player_Position.x += 2;
		}
	}
	if (player1KeyMove == Key::BOMB) {
		std::cout << "drop the bomb!" << std::endl;
		player1.BombPositionIJ = player1.PlayerPositionXY;		
		//ESTO DEBE COMPROBAR SI EN LA POSICIÓN DE LA ONDA EXPANSIVA HAY UN LADRILLO
		std::cout << player1.BombPositionIJ.x << " " << player1.BombPositionIJ.y << std::endl;

		//COMPRUEBA ARRIBA
		if (player1.BombPositionIJ.y > lvl.limiteIJ.y) {
			if (lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y - 1] == casillas::INDESTRUCTIBLE_WALL)
			{
				player1.up = true;
			}
			else
			{
				player1.up = false;
			}

			if (player1.BombPositionIJ.y > lvl.limiteIJ.y + 1 && player1.up == false) {
				if (lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y - 2] == casillas::INDESTRUCTIBLE_WALL)
				{
					player1.up2 = true;
				}
				else
				{
					player1.up2 = false;
				}
			}
		}

		//COMPRUEBA ABAJO
		if (player1.BombPositionIJ.y < lvl.limiteWH.y - 1) {
			if (lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y + 1] == casillas::INDESTRUCTIBLE_WALL)
			{
				player1.down = true;
			}
			else
			{
				player1.down = false;
			}
			if (player1.BombPositionIJ.y < lvl.limiteWH.y - 2 && player1.down == false) {
				if (lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y + 2] == casillas::INDESTRUCTIBLE_WALL)
				{
					player1.down2 = true;
				}
				else
				{
					player1.down2 = false;
				}
			}
		}

		//COMPRUEBA IZQUIERDA
		if (player1.BombPositionIJ.x > lvl.limiteIJ.x) {
			if (lvl.tablero[player1.BombPositionIJ.x - 1][player1.BombPositionIJ.y] == casillas::INDESTRUCTIBLE_WALL)
			{
				player1.left = true;
			}
			else
			{
				player1.left = false;
			}

			if (player1.BombPositionIJ.x > lvl.limiteIJ.x + 1 && player1.left == false) {
				if (lvl.tablero[player1.BombPositionIJ.x - 2][player1.BombPositionIJ.y] == casillas::INDESTRUCTIBLE_WALL)
				{
					player1.left2 = true;
				}
				else
				{
					player1.left2 = false;
				}
			}
		}

		//COMPRUEBA DERECHA
		if (player1.BombPositionIJ.x < lvl.limiteWH.x - 1) {
			if (lvl.tablero[player1.BombPositionIJ.x + 1][player1.BombPositionIJ.y] == casillas::INDESTRUCTIBLE_WALL)
			{
				player1.right = true;
			}
			else
			{
				player1.right = false;
			}

			if (player1.BombPositionIJ.x < lvl.limiteWH.x - 2 && player1.right == false) {
				if (lvl.tablero[player1.BombPositionIJ.x + 2][player1.BombPositionIJ.y] == casillas::INDESTRUCTIBLE_WALL)
				{
					player1.right2 = true;
				}
				else
				{
					player1.right2 = false;
				}
			}
		}

		player1.BombPositionXY = lvl.CasillaACoordenada(player1.BombPositionIJ.x, player1.BombPositionIJ.y);
		player1.dropbomb = true;
	}

	if (player1.bomb.explotando) {
		std::cout << "explosion de la bomba" << std::endl;
		//ARRIBA
		if (player1.BombPositionIJ.y > lvl.limiteIJ.y) {
			if (lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y - 1] == casillas::DESTRUCTIBLE_WALL)
			{
				lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y - 1] = casillas::EMPTY;
			}
			if (player1.BombPositionIJ.y > lvl.limiteIJ.y + 1) {
				if (lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y - 2] == casillas::DESTRUCTIBLE_WALL)
				{
					lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y - 2] = casillas::EMPTY;
				}
			}
		}
		//ABAJO
		if (player1.BombPositionIJ.y < lvl.limiteWH.y - 1) {
			if (lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y + 1] == casillas::DESTRUCTIBLE_WALL)
			{
				lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y + 1] = casillas::EMPTY;
			}
			if (player1.BombPositionIJ.y < lvl.limiteWH.y - 2) {
				if (lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y + 2] == casillas::DESTRUCTIBLE_WALL)
				{
					lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y + 2] = casillas::EMPTY;
				}
			}
		}
		//IZQUIERDA
		if (player1.BombPositionIJ.x > lvl.limiteIJ.x) {
			if (lvl.tablero[player1.BombPositionIJ.x - 1][player1.BombPositionIJ.y] == casillas::DESTRUCTIBLE_WALL)
			{
				lvl.tablero[player1.BombPositionIJ.x - 1][player1.BombPositionIJ.y] = casillas::EMPTY;
			}
			if (player1.BombPositionIJ.x > lvl.limiteIJ.x + 1) {
				if (lvl.tablero[player1.BombPositionIJ.x - 2][player1.BombPositionIJ.y] == casillas::DESTRUCTIBLE_WALL)
				{
					lvl.tablero[player1.BombPositionIJ.x - 2][player1.BombPositionIJ.y] = casillas::EMPTY;
				}
			}
		}
		//DERECHA
		if (player1.BombPositionIJ.x < lvl.limiteWH.x - 1) {
			if (lvl.tablero[player1.BombPositionIJ.x + 1][player1.BombPositionIJ.y] == casillas::DESTRUCTIBLE_WALL)
			{
				lvl.tablero[player1.BombPositionIJ.x + 1][player1.BombPositionIJ.y] = casillas::EMPTY;
			}
			if (player1.BombPositionIJ.x < lvl.limiteWH.x - 2) {
				if (lvl.tablero[player1.BombPositionIJ.x + 2][player1.BombPositionIJ.y] == casillas::DESTRUCTIBLE_WALL)
				{
					lvl.tablero[player1.BombPositionIJ.x + 2][player1.BombPositionIJ.y] = casillas::EMPTY;
				}
			}
		}
	}

	if (player1.PlayerPositionXY.y <= -1) {
		player1.Player_Position.y = LADO_CASILLA + HUD_HEIGHT;
	}
	if (player1.PlayerPositionXY.x <= -1) {
		player1.Player_Position.x = LADO_CASILLA;
	}

	player2KeyMove = player2.Movement(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_RCTRL);
	player2.PlayerPositionXY = lvl.CoordenadaACasilla(player2.Player_Position.x, player2.Player_Position.y);
	//std::cout << player2.Player_ID << " se encuentra en la posicion " << player2.PlayerPositionXY.x << " " << player2.PlayerPositionXY.y << std::endl;



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