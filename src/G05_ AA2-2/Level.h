#pragma once
#include <time.h>
#include "Scene.h"
#include "Types.h"
#include "Constants.h"
#include "GameObject.h"
#include "Bomb.h"

class Level {
public:
	int auxrandomblock;
	int time;
	std::string BG_ID;
	std::string WALL_ID;
	std::string GAMEOBJECT_ID;
	std::string LIMIT_ID;
	SDL_Rect BG_Rect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect Limit_Rect, Limit_Position;
	SDL_Rect Wall_Rect, Wall_Position;
	SDL_Rect GameObject_Rect, GameObject_Position;
	GameState gamestate;
	int casillasAncho, casillasAlto;
	Vector2 limiteIJ, limiteWH;
	casillas **tablero;
	GameObject Destructible_wall;
	GameObject Indestructible_wall;
	GameObject Helmet;
	GameObject Rollers;
	Vector2 DestroyedWall;

	Level();
	~Level();

	Vector2 CasillaACoordenada(int i, int j);
	Vector2 CoordenadaACasilla(int x, int y);


	void Draw();
	void Update(int i, int j);

};

