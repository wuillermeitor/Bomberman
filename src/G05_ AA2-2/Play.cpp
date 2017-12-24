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
	player1.lifes = lives;
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
	player2.lifes = lives;
	player2.score = 0;

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
	hud.Time.text = "Time left:  " + (std::to_string(time));
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
		if (findeljuego || player1.lifes == 0 || player2.lifes == 0) {
			std::cout << "Guanyador, introdueix el teu nom per consola" << std::endl;
			std::cin >> ganador;
			std::cout << " Guanyador introduit" << std::endl;
			std::ofstream fsalida("../../res/files/ranking.bin", std::ios::binary | std::ios::app);
			std::cout << " Obro binari " << std::endl;
			if (player1.score > player2.score) { scoreganador = player1.score; }
			if (player2.score >= player1.score) { scoreganador = player2.score; }
			ganadorRanking = ganador + " " + std::to_string((scoreganador));
			fsalida << ganador << ' ' << scoreganador << ' ';



			std::cout << "En teoria he escrit ganador + score" << std::endl;
			fsalida.close();
			std::cout << " Fitxer binari " << std::endl;
			scenestate = SceneState::GOTOMENU;
			return;
		}
	}
}


void Play::Update() {
	const Uint8 *keyboardstate = SDL_GetKeyboardState(NULL);
	//JUGADOR 1
	player1KeyMove = player1.Movement(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE);
	player1.PlayerPositionXY = lvl.CoordenadaACasilla(player1.Player_Position.x, player1.Player_Position.y - (LADO_CASILLA + 17) / 2);
	player1.PlayerPositionWH = lvl.CoordenadaACasilla(player1.Player_Position.x + LADO_CASILLA - 1, player1.Player_Position.y - ((LADO_CASILLA + 17) / 2) + LADO_CASILLA - 1);
	//POWER UPs
	if (player1.Rollers) {
		player1.speed = 2 * 1.8;
		//debería ser 3.6 pero como se mueve por píxeles y los píxeles son enteros, se trunca a 3 así que el boost es casi inapreciable.
	}
	else {
		player1.speed = 2;
	}

	if (player1.IsPoweredUp) {
		std::cout << player1.timeDown << std::endl;
		std::cout << "player 1 is poweredup so countdown" << std::endl;
		player1.deltaTime = (clock() - player1.lastTime);
		player1.lastTime = clock();
		player1.deltaTime /= CLOCKS_PER_SEC;
		player1.timeDown -= player1.deltaTime;
		if (player1.timeDown <= 0) {
			player1.Rollers = false;
			player1.Helmet = false;
			player1.IsPoweredUp = false;
		}
	}
	else {
		std::cout << "player 1 is no more poweredup" << std::endl;
		player1.lastTime = clock();
		player1.timeDown = 10.;
		player1.deltaTime = 0;
	}
	//MOVIMIENTO
	if (player1KeyMove == Key::UP && player1.PlayerPositionXY.y >= lvl.limiteIJ.y && player1.Player_Position.x >= LADO_CASILLA) {
		if ((lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y] != casillas::INDESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y - 1] != casillas::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y] != casillas::DESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y - 1] != casillas::DESTRUCTIBLE_WALL)) {
			player1.Player_Rect.y = 0;
			player1.Player_Position.y -= player1.speed;
		}
		else if (lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y] != casillas::EMPTY || lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y - 1] != casillas::EMPTY) {
			player1.Player_Position.y += player1.speed;
		}
	}
	else if (player1KeyMove == Key::DOWN && player1.PlayerPositionXY.y + 1 < lvl.limiteWH.y && player1.Player_Position.x >= LADO_CASILLA) {
		if ((lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y + 1] != casillas::INDESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y] != casillas::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y + 1] != casillas::DESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y] != casillas::DESTRUCTIBLE_WALL)){
			player1.Player_Rect.y = player1.Player_Rect.h * 2;
			player1.Player_Position.y += player1.speed;
		}
		else if (lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y + 1] != casillas::EMPTY || lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y] != casillas::EMPTY) {
			player1.Player_Position.y -= player1.speed;
		}
	}
	else if (player1KeyMove == Key::LEFT && player1.PlayerPositionXY.x >= lvl.limiteIJ.x && player1.PlayerPositionWH.x - 1 >= lvl.limiteIJ.x && player1.Player_Position.y >= LADO_CASILLA + HUD_HEIGHT) {
		if ((lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y] != casillas::INDESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPositionWH.x - 1][player1.PlayerPositionWH.y] != casillas::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y] != casillas::DESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPositionWH.x - 1][player1.PlayerPositionWH.y] != casillas::DESTRUCTIBLE_WALL)) {
			player1.Player_Rect.y = player1.Player_Rect.h;
			player1.Player_Position.x -= player1.speed;
		}
		else if (lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y] != casillas::EMPTY || lvl.tablero[player1.PlayerPositionWH.x - 1][player1.PlayerPositionWH.y] != casillas::EMPTY) {
			player1.Player_Position.x += player1.speed;
		}
	}
	else if (player1KeyMove == Key::RIGHT && player1.PlayerPositionXY.x + 1 < lvl.limiteWH.x && player1.Player_Position.y >= LADO_CASILLA + HUD_HEIGHT) {
		if ((lvl.tablero[player1.PlayerPositionXY.x + 1][player1.PlayerPositionXY.y] != casillas::INDESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y] != casillas::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player1.PlayerPositionXY.x + 1][player1.PlayerPositionXY.y] != casillas::DESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y] != casillas::DESTRUCTIBLE_WALL)) {
			player1.Player_Rect.y = player1.Player_Rect.h * 3;
			player1.Player_Position.x += player1.speed;
		}
		else if (lvl.tablero[player1.PlayerPositionXY.x + 1][player1.PlayerPositionXY.y] != casillas::EMPTY || lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y] != casillas::EMPTY) {
			player1.Player_Position.x -= player1.speed;
		}
	}
	//BOMBA
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

	//EXPLOSIÓN DE BOMBA, DESTRUCCIÓN DE MUROS Y DAÑO
	if (player1.bomb.explotando) {
		//ARRIBA
		if (player1.BombPositionIJ.y > lvl.limiteIJ.y && player1.up == false) {
			if (lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y - 1] == casillas::DESTRUCTIBLE_WALL)
			{
				player1.score += WallScore;
				lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y - 1] = casillas::EMPTY;
				lvl.Update(player1.BombPositionIJ.x, player1.BombPositionIJ.y - 1);
			}
			if (player1.BombPositionIJ.y > lvl.limiteIJ.y + 1 && player1.up2 == false) {
				if (lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y - 2] == casillas::DESTRUCTIBLE_WALL)
				{
					player1.score += WallScore;
					lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y - 2] = casillas::EMPTY;
					lvl.Update(player1.BombPositionIJ.x, player1.BombPositionIJ.y - 1);
				}
			}
		}
		//ABAJO
		if (player1.BombPositionIJ.y < lvl.limiteWH.y - 1 && player1.down == false) {
			if (lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y + 1] == casillas::DESTRUCTIBLE_WALL)
			{
				player1.score += WallScore;
				lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y + 1] = casillas::EMPTY;
				lvl.Update(player1.BombPositionIJ.x, player1.BombPositionIJ.y - 1);
			}
			if (player1.BombPositionIJ.y < lvl.limiteWH.y - 2 && player1.down2 == false) {
				if (lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y + 2] == casillas::DESTRUCTIBLE_WALL)
				{
					player1.score += WallScore;
					lvl.tablero[player1.BombPositionIJ.x][player1.BombPositionIJ.y + 2] = casillas::EMPTY;
					lvl.Update(player1.BombPositionIJ.x, player1.BombPositionIJ.y + 2);
				}
			}
		}
		//IZQUIERDA
		if (player1.BombPositionIJ.x > lvl.limiteIJ.x && player1.left == false) {
			if (lvl.tablero[player1.BombPositionIJ.x - 1][player1.BombPositionIJ.y] == casillas::DESTRUCTIBLE_WALL)
			{
				player1.score += WallScore;
				lvl.tablero[player1.BombPositionIJ.x - 1][player1.BombPositionIJ.y] = casillas::EMPTY;
				lvl.Update(player1.BombPositionIJ.x - 1, player1.BombPositionIJ.y);
			}
			if (player1.BombPositionIJ.x > lvl.limiteIJ.x + 1 && player1.left2 == false) {
				if (lvl.tablero[player1.BombPositionIJ.x - 2][player1.BombPositionIJ.y] == casillas::DESTRUCTIBLE_WALL)
				{
					player1.score += WallScore;
					lvl.tablero[player1.BombPositionIJ.x - 2][player1.BombPositionIJ.y] = casillas::EMPTY;
					lvl.Update(player1.BombPositionIJ.x - 2, player1.BombPositionIJ.y);
				}
			}
		}
		//DERECHA
		if (player1.BombPositionIJ.x < lvl.limiteWH.x - 1 && player1.right == false) {
			if (lvl.tablero[player1.BombPositionIJ.x + 1][player1.BombPositionIJ.y] == casillas::DESTRUCTIBLE_WALL)
			{
				player1.score += WallScore;
				lvl.tablero[player1.BombPositionIJ.x + 1][player1.BombPositionIJ.y] = casillas::EMPTY;
				lvl.Update(player1.BombPositionIJ.x + 1, player1.BombPositionIJ.y);
			}
			if (player1.BombPositionIJ.x < lvl.limiteWH.x - 2 && player1.right2 == false) {
				if (lvl.tablero[player1.BombPositionIJ.x + 2][player1.BombPositionIJ.y] == casillas::DESTRUCTIBLE_WALL)
				{
					player1.score += WallScore;
					lvl.tablero[player1.BombPositionIJ.x + 2][player1.BombPositionIJ.y] = casillas::EMPTY;
					lvl.Update(player1.BombPositionIJ.x + 2, player1.BombPositionIJ.y);
				}
			}
		}

		//DAÑO DE TU PROPIA BOMBA
		if (!player1.alreadyDamaged) {
			if ((player1.BombPositionIJ.x == player1.PlayerPositionXY.x && player1.BombPositionIJ.y - 1 == player1.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x == player1.PlayerPositionWH.x && player1.BombPositionIJ.y - 1 == player1.PlayerPositionWH.y)
				|| (player1.BombPositionIJ.x == player1.PlayerPositionXY.x && player1.BombPositionIJ.y - 2 == player1.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x == player1.PlayerPositionWH.x && player1.BombPositionIJ.y - 2 == player1.PlayerPositionWH.y)
				|| (player1.BombPositionIJ.x == player1.PlayerPositionXY.x && player1.BombPositionIJ.y + 1 == player1.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x == player1.PlayerPositionWH.x && player1.BombPositionIJ.y + 1 == player1.PlayerPositionWH.y)
				|| (player1.BombPositionIJ.x == player1.PlayerPositionXY.x && player1.BombPositionIJ.y + 2 == player1.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x == player1.PlayerPositionWH.x && player1.BombPositionIJ.y + 2 == player1.PlayerPositionWH.y)
				|| (player1.BombPositionIJ.x - 1 == player1.PlayerPositionXY.x && player1.BombPositionIJ.y == player1.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x - 1 == player1.PlayerPositionWH.x && player1.BombPositionIJ.y == player1.PlayerPositionWH.y)
				|| (player1.BombPositionIJ.x - 2 == player1.PlayerPositionXY.x && player1.BombPositionIJ.y == player1.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x - 2 == player1.PlayerPositionWH.x && player1.BombPositionIJ.y == player1.PlayerPositionWH.y)
				|| (player1.BombPositionIJ.x + 1 == player1.PlayerPositionXY.x && player1.BombPositionIJ.y == player1.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x + 1 == player1.PlayerPositionWH.x && player1.BombPositionIJ.y == player1.PlayerPositionWH.y)
				|| (player1.BombPositionIJ.x + 2 == player1.PlayerPositionXY.x && player1.BombPositionIJ.y == player1.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x + 2 == player1.PlayerPositionWH.x && player1.BombPositionIJ.y == player1.PlayerPositionWH.y)) {
				if (player1.Helmet) {
					player1.Helmet = false;
					player1.IsPoweredUp = false;
					player1.alreadyDamaged = true;
				}
				else {
					std::cout << "oh no" << std::endl;
					player1.lifes -= 1;
					player1.alreadyDamaged = true;
				}
			}
		}
		//DAÑO AL OTRO JUGADOR
		if (!player2.alreadyDamaged) {
			if ((player1.BombPositionIJ.x == player2.PlayerPositionXY.x && player1.BombPositionIJ.y - 1 == player2.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x == player2.PlayerPositionWH.x && player1.BombPositionIJ.y - 1 == player2.PlayerPositionWH.y)
				|| (player1.BombPositionIJ.x == player2.PlayerPositionXY.x && player1.BombPositionIJ.y - 2 == player2.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x == player2.PlayerPositionWH.x && player1.BombPositionIJ.y - 2 == player2.PlayerPositionWH.y)
				|| (player1.BombPositionIJ.x == player2.PlayerPositionXY.x && player1.BombPositionIJ.y + 1 == player2.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x == player2.PlayerPositionWH.x && player1.BombPositionIJ.y + 1 == player2.PlayerPositionWH.y)
				|| (player1.BombPositionIJ.x == player2.PlayerPositionXY.x && player1.BombPositionIJ.y + 2 == player2.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x == player2.PlayerPositionWH.x && player1.BombPositionIJ.y + 2 == player2.PlayerPositionWH.y)
				|| (player1.BombPositionIJ.x - 1 == player2.PlayerPositionXY.x && player1.BombPositionIJ.y == player2.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x - 1 == player2.PlayerPositionWH.x && player1.BombPositionIJ.y == player2.PlayerPositionWH.y)
				|| (player1.BombPositionIJ.x - 2 == player2.PlayerPositionXY.x && player1.BombPositionIJ.y == player2.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x - 2 == player2.PlayerPositionWH.x && player1.BombPositionIJ.y == player2.PlayerPositionWH.y)
				|| (player1.BombPositionIJ.x + 1 == player2.PlayerPositionXY.x && player1.BombPositionIJ.y == player2.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x + 1 == player2.PlayerPositionWH.x && player1.BombPositionIJ.y == player2.PlayerPositionWH.y)
				|| (player1.BombPositionIJ.x + 2 == player2.PlayerPositionXY.x && player1.BombPositionIJ.y == player2.PlayerPositionXY.y)
				|| (player1.BombPositionIJ.x + 2 == player2.PlayerPositionWH.x && player1.BombPositionIJ.y == player2.PlayerPositionWH.y)) {
				if (player2.Helmet) {
					player2.Helmet = false;
					player2.IsPoweredUp = false;
					player2.alreadyDamaged = true;
				}
				else {
					player2.lifes -= 1;
					player2.alreadyDamaged = true;
					player1.score += 100;
				}
			}
		}
	}
	else if (!player1.bomb.explotando && !player2.bomb.explotando) {
		player1.alreadyDamaged = false;
		player2.alreadyDamaged = false;
	}

	//CORRECCIÓN DE POSICIÓN
	if (player1.PlayerPositionXY.y <= -1) {
		player1.Player_Position.y = LADO_CASILLA + HUD_HEIGHT;
	}
	if (player1.PlayerPositionXY.x <= -1) {
		player1.Player_Position.x = LADO_CASILLA;
	}

	//COMPROBACIÓN DE SI HA COGIDO UN POWER UP
	if (player1.PlayerPositionXY.y >=0 && player1.PlayerPositionXY.x >=0 && player1.PlayerPositionWH.x<lvl.limiteWH.x && player1.PlayerPositionWH.y<lvl.limiteWH.y && !player1.IsPoweredUp) {
		if (lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y] == casillas::ROLLERS || lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y] == casillas::ROLLERS) {
			lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y] = casillas::EMPTY;
			lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y] = casillas::EMPTY;
			player1.Rollers = true;
			player1.IsPoweredUp = true;
		}
		if (lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y] == casillas::HELMET || lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y] == casillas::HELMET) {
			lvl.tablero[player1.PlayerPositionXY.x][player1.PlayerPositionXY.y] = casillas::EMPTY;
			lvl.tablero[player1.PlayerPositionWH.x][player1.PlayerPositionWH.y] = casillas::EMPTY;
			player1.Helmet = true;
			player1.IsPoweredUp = true;
		}
	}


	//JUGADOR 2
	player2KeyMove = player2.Movement(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_RCTRL);
	player2.PlayerPositionXY = lvl.CoordenadaACasilla(player2.Player_Position.x, player2.Player_Position.y - (LADO_CASILLA + 17) / 2);
	player2.PlayerPositionWH = lvl.CoordenadaACasilla(player2.Player_Position.x + LADO_CASILLA - 1, player2.Player_Position.y - ((LADO_CASILLA + 17) / 2) + LADO_CASILLA - 1);
	//POWER UPs
	if (player2.Rollers) {
		player2.speed = 2 * 1.8;
		//debería ser 3.6 pero como se mueve por píxeles y los píxeles son enteros, se trunca a 3 así que el boost es casi inapreciable.
	}
	else {
		player2.speed = 2;
	}

	if (player2.IsPoweredUp) {
		player2.deltaTime = (clock() - player2.lastTime);
		player2.lastTime = clock();
		player2.deltaTime /= CLOCKS_PER_SEC;
		player2.timeDown -= player2.deltaTime;
		if (player2.timeDown <= 0) {
			player2.Rollers = false;
			player2.Helmet = false;
			player2.IsPoweredUp = false;
		}
	}
	else {
		player2.lastTime = clock();
		player2.timeDown = 10.;
		player2.deltaTime = 0;
	}
	//MOVIMIENTO
	if (player2KeyMove == Key::UP && player2.PlayerPositionXY.y >= lvl.limiteIJ.y && player2.Player_Position.x >= LADO_CASILLA) {
		if ((lvl.tablero[player2.PlayerPositionXY.x][player2.PlayerPositionXY.y] != casillas::INDESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPositionWH.x][player2.PlayerPositionWH.y - 1] != casillas::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player2.PlayerPositionXY.x][player2.PlayerPositionXY.y] != casillas::DESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPositionWH.x][player2.PlayerPositionWH.y - 1] != casillas::DESTRUCTIBLE_WALL)) {
			player2.Player_Rect.y = 0;
			player2.Player_Position.y -= player2.speed;
		}
		else if (lvl.tablero[player2.PlayerPositionXY.x][player2.PlayerPositionXY.y] != casillas::EMPTY || lvl.tablero[player2.PlayerPositionWH.x][player2.PlayerPositionWH.y - 1] != casillas::EMPTY) {
			player2.Player_Position.y += player2.speed;
		}
	}
	else if (player2KeyMove == Key::DOWN && player2.PlayerPositionXY.y + 1 < lvl.limiteWH.y && player2.Player_Position.x >= LADO_CASILLA) {
		if ((lvl.tablero[player2.PlayerPositionXY.x][player2.PlayerPositionXY.y + 1] != casillas::INDESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPositionWH.x][player2.PlayerPositionWH.y] != casillas::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player2.PlayerPositionXY.x][player2.PlayerPositionXY.y + 1] != casillas::DESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPositionWH.x][player2.PlayerPositionWH.y] != casillas::DESTRUCTIBLE_WALL)) {
			player2.Player_Rect.y = player2.Player_Rect.h * 2;
			player2.Player_Position.y += player2.speed;
		}
		else if (lvl.tablero[player2.PlayerPositionXY.x][player2.PlayerPositionXY.y + 1] != casillas::EMPTY || lvl.tablero[player2.PlayerPositionWH.x][player2.PlayerPositionWH.y] != casillas::EMPTY) {
			player2.Player_Position.y -= player2.speed;
		}
	}
	else if (player2KeyMove == Key::LEFT && player2.PlayerPositionXY.x >= lvl.limiteIJ.x && player2.PlayerPositionWH.x - 1 >= lvl.limiteIJ.x && player2.Player_Position.y >= LADO_CASILLA + HUD_HEIGHT) {
		if ((lvl.tablero[player2.PlayerPositionXY.x][player2.PlayerPositionXY.y] != casillas::INDESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPositionWH.x - 1][player2.PlayerPositionWH.y] != casillas::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player2.PlayerPositionXY.x][player2.PlayerPositionXY.y] != casillas::DESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPositionWH.x - 1][player2.PlayerPositionWH.y] != casillas::DESTRUCTIBLE_WALL)) {
			player2.Player_Rect.y = player2.Player_Rect.h;
			player2.Player_Position.x -= player2.speed;
		}
		else if (lvl.tablero[player2.PlayerPositionXY.x][player2.PlayerPositionXY.y] != casillas::EMPTY || lvl.tablero[player2.PlayerPositionWH.x - 1][player2.PlayerPositionWH.y] != casillas::EMPTY) {
			player2.Player_Position.x += player2.speed;
		}
	}
	else if (player2KeyMove == Key::RIGHT && player2.PlayerPositionXY.x + 1 < lvl.limiteWH.x && player2.Player_Position.y >= LADO_CASILLA + HUD_HEIGHT) {
		if ((lvl.tablero[player2.PlayerPositionXY.x + 1][player2.PlayerPositionXY.y] != casillas::INDESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPositionWH.x][player2.PlayerPositionWH.y] != casillas::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player2.PlayerPositionXY.x + 1][player2.PlayerPositionXY.y] != casillas::DESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPositionWH.x][player2.PlayerPositionWH.y] != casillas::DESTRUCTIBLE_WALL)) {
			player2.Player_Rect.y = player2.Player_Rect.h * 3;
			player2.Player_Position.x += player2.speed;
		}
		else if (lvl.tablero[player2.PlayerPositionXY.x + 1][player2.PlayerPositionXY.y] != casillas::EMPTY || lvl.tablero[player2.PlayerPositionWH.x][player2.PlayerPositionWH.y] != casillas::EMPTY) {
			player2.Player_Position.x -= player2.speed;
		}
	}
	//BOMBA
	if (player2KeyMove == Key::BOMB) {
		std::cout << "drop the bomb!" << std::endl;
		player2.BombPositionIJ = player2.PlayerPositionXY;
		//ESTO DEBE COMPROBAR SI EN LA POSICIÓN DE LA ONDA EXPANSIVA HAY UN LADRILLO
		std::cout << player2.BombPositionIJ.x << " " << player2.BombPositionIJ.y << std::endl;

		//COMPRUEBA ARRIBA
		if (player2.BombPositionIJ.y > lvl.limiteIJ.y) {
			if (lvl.tablero[player2.BombPositionIJ.x][player2.BombPositionIJ.y - 1] == casillas::INDESTRUCTIBLE_WALL)
			{
				player2.up = true;
			}
			else
			{
				player2.up = false;
			}

			if (player2.BombPositionIJ.y > lvl.limiteIJ.y + 1 && player2.up == false) {
				if (lvl.tablero[player2.BombPositionIJ.x][player2.BombPositionIJ.y - 2] == casillas::INDESTRUCTIBLE_WALL)
				{
					player2.up2 = true;
				}
				else
				{
					player2.up2 = false;
				}
			}
		}

		//COMPRUEBA ABAJO
		if (player2.BombPositionIJ.y < lvl.limiteWH.y - 1) {
			if (lvl.tablero[player2.BombPositionIJ.x][player2.BombPositionIJ.y + 1] == casillas::INDESTRUCTIBLE_WALL)
			{
				player2.down = true;
			}
			else
			{
				player2.down = false;
			}
			if (player2.BombPositionIJ.y < lvl.limiteWH.y - 2 && player2.down == false) {
				if (lvl.tablero[player2.BombPositionIJ.x][player2.BombPositionIJ.y + 2] == casillas::INDESTRUCTIBLE_WALL)
				{
					player2.down2 = true;
				}
				else
				{
					player2.down2 = false;
				}
			}
		}

		//COMPRUEBA IZQUIERDA
		if (player2.BombPositionIJ.x > lvl.limiteIJ.x) {
			if (lvl.tablero[player2.BombPositionIJ.x - 1][player2.BombPositionIJ.y] == casillas::INDESTRUCTIBLE_WALL)
			{
				player2.left = true;
			}
			else
			{
				player2.left = false;
			}

			if (player2.BombPositionIJ.x > lvl.limiteIJ.x + 1 && player2.left == false) {
				if (lvl.tablero[player2.BombPositionIJ.x - 2][player2.BombPositionIJ.y] == casillas::INDESTRUCTIBLE_WALL)
				{
					player2.left2 = true;
				}
				else
				{
					player2.left2 = false;
				}
			}
		}

		//COMPRUEBA DERECHA
		if (player2.BombPositionIJ.x < lvl.limiteWH.x - 1) {
			if (lvl.tablero[player2.BombPositionIJ.x + 1][player2.BombPositionIJ.y] == casillas::INDESTRUCTIBLE_WALL)
			{
				player2.right = true;
			}
			else
			{
				player2.right = false;
			}

			if (player2.BombPositionIJ.x < lvl.limiteWH.x - 2 && player2.right == false) {
				if (lvl.tablero[player2.BombPositionIJ.x + 2][player2.BombPositionIJ.y] == casillas::INDESTRUCTIBLE_WALL)
				{
					player2.right2 = true;
				}
				else
				{
					player2.right2 = false;
				}
			}
		}

		player2.BombPositionXY = lvl.CasillaACoordenada(player2.BombPositionIJ.x, player2.BombPositionIJ.y);
		player2.dropbomb = true;
	}

	//EXPLOSIÓN DE BOMBA, DESTRUCCIÓN DE MUROS Y DAÑO
	if (player2.bomb.explotando) {
		//ARRIBA
		if (player2.BombPositionIJ.y > lvl.limiteIJ.y && player2.up == false) {
			if (lvl.tablero[player2.BombPositionIJ.x][player2.BombPositionIJ.y - 1] == casillas::DESTRUCTIBLE_WALL)
			{
				player2.score += WallScore;
				lvl.tablero[player2.BombPositionIJ.x][player2.BombPositionIJ.y - 1] = casillas::EMPTY;
				lvl.Update(player2.BombPositionIJ.x, player2.BombPositionIJ.y - 1);
			}
			if (player2.BombPositionIJ.y > lvl.limiteIJ.y + 1 && player2.up2 == false) {
				if (lvl.tablero[player2.BombPositionIJ.x][player2.BombPositionIJ.y - 2] == casillas::DESTRUCTIBLE_WALL)
				{
					player2.score += WallScore;
					lvl.tablero[player2.BombPositionIJ.x][player2.BombPositionIJ.y - 2] = casillas::EMPTY;
					lvl.Update(player2.BombPositionIJ.x, player2.BombPositionIJ.y - 1);
				}
			}
		}
		//ABAJO
		if (player2.BombPositionIJ.y < lvl.limiteWH.y - 1 && player2.down == false) {
			if (lvl.tablero[player2.BombPositionIJ.x][player2.BombPositionIJ.y + 1] == casillas::DESTRUCTIBLE_WALL)
			{
				player2.score += WallScore;
				lvl.tablero[player2.BombPositionIJ.x][player2.BombPositionIJ.y + 1] = casillas::EMPTY;
				lvl.Update(player2.BombPositionIJ.x, player2.BombPositionIJ.y - 1);
			}
			if (player2.BombPositionIJ.y < lvl.limiteWH.y - 2 && player2.down2 == false) {
				if (lvl.tablero[player2.BombPositionIJ.x][player2.BombPositionIJ.y + 2] == casillas::DESTRUCTIBLE_WALL)
				{
					player2.score += WallScore;
					lvl.tablero[player2.BombPositionIJ.x][player2.BombPositionIJ.y + 2] = casillas::EMPTY;
					lvl.Update(player2.BombPositionIJ.x, player2.BombPositionIJ.y + 2);
				}
			}
		}
		//IZQUIERDA
		if (player2.BombPositionIJ.x > lvl.limiteIJ.x && player2.left == false) {
			if (lvl.tablero[player2.BombPositionIJ.x - 1][player2.BombPositionIJ.y] == casillas::DESTRUCTIBLE_WALL)
			{
				player2.score += WallScore;
				lvl.tablero[player2.BombPositionIJ.x - 1][player2.BombPositionIJ.y] = casillas::EMPTY;
				lvl.Update(player2.BombPositionIJ.x - 1, player2.BombPositionIJ.y);
			}
			if (player2.BombPositionIJ.x > lvl.limiteIJ.x + 1 && player2.left2 == false) {
				if (lvl.tablero[player2.BombPositionIJ.x - 2][player2.BombPositionIJ.y] == casillas::DESTRUCTIBLE_WALL)
				{
					player2.score += WallScore;
					lvl.tablero[player2.BombPositionIJ.x - 2][player2.BombPositionIJ.y] = casillas::EMPTY;
					lvl.Update(player2.BombPositionIJ.x - 2, player2.BombPositionIJ.y);
				}
			}
		}
		//DERECHA
		if (player2.BombPositionIJ.x < lvl.limiteWH.x - 1 && player2.right == false) {
			if (lvl.tablero[player2.BombPositionIJ.x + 1][player2.BombPositionIJ.y] == casillas::DESTRUCTIBLE_WALL)
			{
				player2.score += WallScore;
				lvl.tablero[player2.BombPositionIJ.x + 1][player2.BombPositionIJ.y] = casillas::EMPTY;
				lvl.Update(player2.BombPositionIJ.x + 1, player2.BombPositionIJ.y);
			}
			if (player2.BombPositionIJ.x < lvl.limiteWH.x - 2 && player2.right2 == false) {
				if (lvl.tablero[player2.BombPositionIJ.x + 2][player2.BombPositionIJ.y] == casillas::DESTRUCTIBLE_WALL)
				{
					player2.score += WallScore;
					lvl.tablero[player2.BombPositionIJ.x + 2][player2.BombPositionIJ.y] = casillas::EMPTY;
					lvl.Update(player2.BombPositionIJ.x + 2, player2.BombPositionIJ.y);
				}
			}
		}

		//DAÑO DE TU PROPIA BOMBA
		if (!player2.alreadyDamaged) {
			if ((player2.BombPositionIJ.x == player2.PlayerPositionXY.x && player2.BombPositionIJ.y - 1 == player2.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x == player2.PlayerPositionWH.x && player2.BombPositionIJ.y - 1 == player2.PlayerPositionWH.y)
				|| (player2.BombPositionIJ.x == player2.PlayerPositionXY.x && player2.BombPositionIJ.y - 2 == player2.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x == player2.PlayerPositionWH.x && player2.BombPositionIJ.y - 2 == player2.PlayerPositionWH.y)
				|| (player2.BombPositionIJ.x == player2.PlayerPositionXY.x && player2.BombPositionIJ.y + 1 == player2.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x == player2.PlayerPositionWH.x && player2.BombPositionIJ.y + 1 == player2.PlayerPositionWH.y)
				|| (player2.BombPositionIJ.x == player2.PlayerPositionXY.x && player2.BombPositionIJ.y + 2 == player2.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x == player2.PlayerPositionWH.x && player2.BombPositionIJ.y + 2 == player2.PlayerPositionWH.y)
				|| (player2.BombPositionIJ.x - 1 == player2.PlayerPositionXY.x && player2.BombPositionIJ.y == player2.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x - 1 == player2.PlayerPositionWH.x && player2.BombPositionIJ.y == player2.PlayerPositionWH.y)
				|| (player2.BombPositionIJ.x - 2 == player2.PlayerPositionXY.x && player2.BombPositionIJ.y == player2.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x - 2 == player2.PlayerPositionWH.x && player2.BombPositionIJ.y == player2.PlayerPositionWH.y)
				|| (player2.BombPositionIJ.x + 1 == player2.PlayerPositionXY.x && player2.BombPositionIJ.y == player2.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x + 1 == player2.PlayerPositionWH.x && player2.BombPositionIJ.y == player2.PlayerPositionWH.y)
				|| (player2.BombPositionIJ.x + 2 == player2.PlayerPositionXY.x && player2.BombPositionIJ.y == player2.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x + 2 == player2.PlayerPositionWH.x && player2.BombPositionIJ.y == player2.PlayerPositionWH.y)) {
				if (player2.Helmet) {
					player2.Helmet = false;
					player2.IsPoweredUp = false;
					player2.alreadyDamaged = true;
				}
				else {
					player2.lifes -= 1;
					player2.alreadyDamaged = true;
				}
			}
		}
		//DAÑO AL OTRO JUGADOR
		if (!player1.alreadyDamaged) {
			if ((player2.BombPositionIJ.x == player1.PlayerPositionXY.x && player2.BombPositionIJ.y - 1 == player1.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x == player1.PlayerPositionWH.x && player2.BombPositionIJ.y - 1 == player1.PlayerPositionWH.y)
				|| (player2.BombPositionIJ.x == player1.PlayerPositionXY.x && player2.BombPositionIJ.y - 2 == player1.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x == player1.PlayerPositionWH.x && player2.BombPositionIJ.y - 2 == player1.PlayerPositionWH.y)
				|| (player2.BombPositionIJ.x == player1.PlayerPositionXY.x && player2.BombPositionIJ.y + 1 == player1.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x == player1.PlayerPositionWH.x && player2.BombPositionIJ.y + 1 == player1.PlayerPositionWH.y)
				|| (player2.BombPositionIJ.x == player1.PlayerPositionXY.x && player2.BombPositionIJ.y + 2 == player1.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x == player1.PlayerPositionWH.x && player2.BombPositionIJ.y + 2 == player1.PlayerPositionWH.y)
				|| (player2.BombPositionIJ.x - 1 == player1.PlayerPositionXY.x && player2.BombPositionIJ.y == player1.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x - 1 == player1.PlayerPositionWH.x && player2.BombPositionIJ.y == player1.PlayerPositionWH.y)
				|| (player2.BombPositionIJ.x - 2 == player1.PlayerPositionXY.x && player2.BombPositionIJ.y == player1.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x - 2 == player1.PlayerPositionWH.x && player2.BombPositionIJ.y == player1.PlayerPositionWH.y)
				|| (player2.BombPositionIJ.x + 1 == player1.PlayerPositionXY.x && player2.BombPositionIJ.y == player1.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x + 1 == player1.PlayerPositionWH.x && player2.BombPositionIJ.y == player1.PlayerPositionWH.y)
				|| (player2.BombPositionIJ.x + 2 == player1.PlayerPositionXY.x && player2.BombPositionIJ.y == player1.PlayerPositionXY.y)
				|| (player2.BombPositionIJ.x + 2 == player1.PlayerPositionWH.x && player2.BombPositionIJ.y == player1.PlayerPositionWH.y)) {
				if (player1.Helmet) {
					player1.Helmet = false;
					player1.IsPoweredUp = false;
					player1.alreadyDamaged = true;
				}
				else {
					player1.lifes -= 1;
					player1.alreadyDamaged = true;
					player2.score += 100;
				}
			}
		}
	}
	else if(!player2.bomb.explotando && !player1.bomb.explotando){
		player1.alreadyDamaged = false;
		player2.alreadyDamaged = false;
	}

	//CORRECCIÓN DE POSICIÓN
	if (player2.PlayerPositionXY.y <= -1) {
		player2.Player_Position.y = LADO_CASILLA + HUD_HEIGHT;
	}
	if (player2.PlayerPositionXY.x <= -1) {
		player2.Player_Position.x = LADO_CASILLA;
	}

	//COMPROBACIÓN DE SI HA COGIDO UN POWER UP
	if (player2.PlayerPositionXY.y >= 0 && player2.PlayerPositionXY.x >= 0 && player2.PlayerPositionWH.x<lvl.limiteWH.x && player2.PlayerPositionWH.y<lvl.limiteWH.y && !player2.IsPoweredUp) {
		if (lvl.tablero[player2.PlayerPositionXY.x][player2.PlayerPositionXY.y] == casillas::ROLLERS || lvl.tablero[player2.PlayerPositionWH.x][player2.PlayerPositionWH.y] == casillas::ROLLERS) {
			lvl.tablero[player2.PlayerPositionXY.x][player2.PlayerPositionXY.y] = casillas::EMPTY;
			lvl.tablero[player2.PlayerPositionWH.x][player2.PlayerPositionWH.y] = casillas::EMPTY;
			player2.Rollers = true;
			player2.IsPoweredUp = true;
		}
		if (lvl.tablero[player2.PlayerPositionXY.x][player2.PlayerPositionXY.y] == casillas::HELMET || lvl.tablero[player2.PlayerPositionWH.x][player2.PlayerPositionWH.y] == casillas::HELMET) {
			lvl.tablero[player2.PlayerPositionXY.x][player2.PlayerPositionXY.y] = casillas::EMPTY;
			lvl.tablero[player2.PlayerPositionWH.x][player2.PlayerPositionWH.y] = casillas::EMPTY;
			player2.Helmet = true;
			player2.IsPoweredUp = true;
		}
	}


	//Clock Update
	if (time > 0) {
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		time -= deltaTime;
		//std::cout << timeDown << std::endl;
		hud.Time.text = "Time left:  " + (std::to_string(static_cast<int>(time)));
		std::cout << lastTime << std::endl;
	}
	if (time <= 0) {
		//std::cout << "FIN DEL JUEGO" << std::endl;
		hud.Time.text = "FIN DEL JUEGO";
		findeljuego = true;
	}
	hud.P1score.text = "Score p1:  " + std::to_string(player1.score);
	hud.P2score.text = "Score p2:  " + std::to_string(player2.score);
	hud.P1lifes.text = "Lifes p1:  " + std::to_string(player1.lifes);
	hud.P2lifes.text = "Lifes p2:  " + std::to_string(player2.lifes);
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