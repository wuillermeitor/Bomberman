#include "Level.h"




Level::Level()
{
	Renderer::Instance()->LoadTexture(BACKGROUND, "../../res/img/bgGame.jpg");
	casillasAncho = 13;
	casillasAlto = 11;

	Indestructible_wall = GameObject();
	Indestructible_wall.GameObject_ID = INDESTRUCTIBLE_WALL;
	Renderer::Instance()->LoadTexture(Indestructible_wall.GameObject_ID, Indestructible_wall.GameObjectPath);
	Renderer::Instance()->GetTextureSize(Indestructible_wall.GameObject_ID);
	Indestructible_wall.frameWidth = (Indestructible_wall.textWidth / 3);
	Indestructible_wall.frameHeight = (Indestructible_wall.textHeight / 2);
	Indestructible_wall.GameObject_Position.x = 0;
	Indestructible_wall.GameObject_Position.y = 0;
	Indestructible_wall.GameObject_Rect.x = 0;
	Indestructible_wall.GameObject_Rect.y = 0;
	Indestructible_wall.GameObject_Position.h = LADO_CASILLA;
	Indestructible_wall.GameObject_Rect.h = Indestructible_wall.frameHeight;
	Indestructible_wall.GameObject_Position.w = LADO_CASILLA;
	Indestructible_wall.GameObject_Rect.w = Indestructible_wall.frameWidth;

	Destructible_wall = GameObject();
	Destructible_wall.GameObject_ID = DESTRUCTIBLE_WALL;
	Renderer::Instance()->LoadTexture(Destructible_wall.GameObject_ID, Destructible_wall.GameObjectPath);
	Renderer::Instance()->GetTextureSize(Destructible_wall.GameObject_ID);
	Destructible_wall.frameWidth = (Destructible_wall.textWidth / 3);
	Destructible_wall.frameHeight = (Destructible_wall.textHeight / 2);
	Destructible_wall.GameObject_Position.x = 0;
	Destructible_wall.GameObject_Position.y = 0;
	Destructible_wall.GameObject_Rect.x = Destructible_wall.frameWidth;
	Destructible_wall.GameObject_Rect.y = 0;
	Destructible_wall.GameObject_Position.h = LADO_CASILLA;
	Destructible_wall.GameObject_Rect.h = Destructible_wall.frameHeight;
	Destructible_wall.GameObject_Position.w = LADO_CASILLA;
	Destructible_wall.GameObject_Rect.w = Destructible_wall.frameWidth;

	Helmet = GameObject();
	Helmet.GameObject_ID = HELMET;
	Renderer::Instance()->LoadTexture(Helmet.GameObject_ID, Helmet.GameObjectPath);
	Renderer::Instance()->GetTextureSize(Helmet.GameObject_ID);
	Helmet.frameWidth = (Helmet.textWidth / 3);
	Helmet.frameHeight = (Helmet.textHeight / 2);
	Helmet.GameObject_Position.x = 0;
	Helmet.GameObject_Position.y = 0;
	Helmet.GameObject_Rect.x = Helmet.frameWidth * 2;
	Helmet.GameObject_Rect.y = Helmet.frameHeight;
	Helmet.GameObject_Position.h = LADO_CASILLA;
	Helmet.GameObject_Rect.h = Helmet.frameHeight;
	Helmet.GameObject_Position.w = LADO_CASILLA;
	Helmet.GameObject_Rect.w = Helmet.frameWidth;

	Rollers = GameObject();
	Rollers.GameObject_ID = ROLLER;
	Renderer::Instance()->LoadTexture(Rollers.GameObject_ID, Rollers.GameObjectPath);
	Renderer::Instance()->GetTextureSize(Rollers.GameObject_ID);
	Rollers.frameWidth = (Rollers.textWidth / 3);
	Rollers.frameHeight = (Rollers.textHeight / 2);
	Rollers.GameObject_Position.x = 0;
	Rollers.GameObject_Position.y = 0;
	Rollers.GameObject_Rect.x = Rollers.frameWidth;
	Rollers.GameObject_Rect.y = Rollers.frameHeight;
	Rollers.GameObject_Position.h = LADO_CASILLA;
	Rollers.GameObject_Rect.h = Rollers.frameHeight;
	Rollers.GameObject_Position.w = LADO_CASILLA;
	Rollers.GameObject_Rect.w = Rollers.frameWidth;

	tablero = new casillas*[casillasAncho];
	for (int i = 0; i <= casillasAncho; i++) {
		tablero[i] = new casillas[casillasAlto];
		for (int j = 0; j <= casillasAlto; j++) {
			tablero[i][j] = casillas::EMPTY;
		}
	}
	limiteIJ = { 0, 0 };
	limiteWH = { casillasAncho, casillasAlto };

}


Level::~Level()
{

}

Vector2 Level::CoordenadaACasilla(int x, int y)
{
	int iCoordenada;
	int jCoordenada;
	iCoordenada = (x / LADO_CASILLA) - 1;
	jCoordenada = (y / LADO_CASILLA) - (HUD_HEIGHT / LADO_CASILLA) - 1;
	Vector2 casilla{ iCoordenada, jCoordenada };
	return casilla;
}

Vector2 Level::CasillaACoordenada(int i, int j)
{
	int iCasilla;
	int jCasilla;
	iCasilla = (i * LADO_CASILLA) + LADO_CASILLA;
	jCasilla = (j * LADO_CASILLA) + HUD_HEIGHT + LADO_CASILLA;
	Vector2 coordenada{ iCasilla, jCasilla };
	return coordenada;
}

void Level::Draw()
{
	for (int i = 0; i < casillasAncho; ++i) {
		for (int j = 0; j < casillasAlto; ++j) {
			if (tablero[i][j] == casillas::INDESTRUCTIBLE_WALL) {
				Vector2 coordenadas = CasillaACoordenada(i, j);
				Indestructible_wall.draw(Indestructible_wall.GameObject_ID, coordenadas.x, coordenadas.y);
			}
			else if (tablero[i][j] == casillas::DESTRUCTIBLE_WALL) {
				Vector2 coordenadas = CasillaACoordenada(i, j);
				Destructible_wall.draw(Destructible_wall.GameObject_ID, coordenadas.x, coordenadas.y);
			}
			else if (tablero[i][j] == casillas::HELMET) {
				Vector2 coordenadas = CasillaACoordenada(i, j);
				Helmet.draw(Helmet.GameObject_ID, coordenadas.x, coordenadas.y);
			}
			else if (tablero[i][j] == casillas::ROLLERS) {
				Vector2 coordenadas = CasillaACoordenada(i, j);
				Rollers.draw(Rollers.GameObject_ID, coordenadas.x, coordenadas.y);
			}
		}
	}
}

void Level::Update(int i, int j)
{
	//std::cout << "entro en update del lvl" << std::endl;
	if (rand() % 100 <= 19) {
		if (rand() % 100 <= 49) {
			tablero[i][j] = casillas::HELMET;
		}
		else {
			tablero[i][j] = casillas::ROLLERS;
		}
		//std::cout << "power-up" << std::endl;
	}
}

