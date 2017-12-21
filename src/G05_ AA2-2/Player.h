#pragma once
#include <iostream>
#include "Renderer.h"
#include "Bomb.h"

class Player
{
public:
	//Variables
	std::string Player_ID, PlayerPath;
	SDL_Rect Player_Rect, Player_Position;
	int textWidth = 192;
	int textHeight = 94;
	int frameWidth, frameHeight;
	int frameTime;
	int cambiop = 1;
	bool dropbomb = false;
	int dropX, dropY;
	int lifes, score;
	bool Rollers = false;
	bool Helmet = false;
	int speed = 5;
	int RollersBoost = 1.8;
	Vector2 PlayerPositionXY;
	Vector2 PlayerPositionWH;
	Vector2 posicionBomba;
	Bomb bomb;
	bool up = false;
	bool up2 = false;
	bool down = false;
	bool down2 = false;
	bool left = false;
	bool left2 = false;
	bool right = false;
	bool right2 = false;


	//Métodos
	Player();
	~Player();
	void EventHandler(SDL_Event evento);
	Key Movement(SDL_Scancode UP, SDL_Scancode DOWN, SDL_Scancode LEFT, SDL_Scancode RIGHT, SDL_Scancode DropBomb);
	void Draw();
	void SpawnBomba(int i, int j, bool up, bool up2, bool down, bool down2, bool left, bool left2, bool right, bool right2);

};