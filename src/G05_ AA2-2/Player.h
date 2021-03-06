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
	bool IsPoweredUp = false;
	int speed = 2;	
	bool alreadyDamaged = false;
	clock_t lastTime = clock();
	float timeDown = 10.;
	float deltaTime = 0;

	Vector2 PlayerPositionXY;
	Vector2 PlayerPositionWH;
	Vector2 BombPositionXY;
	Vector2 BombPositionIJ;
	Bomb bomb;
	bool up = true;
	bool up2 = true;
	bool down = true;
	bool down2 = true;
	bool left = true;
	bool left2 = true;
	bool right = true;
	bool right2 = true;


	//M�todos
	Player();
	~Player();
	void EventHandler(SDL_Event evento);
	Key Movement(SDL_Scancode UP, SDL_Scancode DOWN, SDL_Scancode LEFT, SDL_Scancode RIGHT, SDL_Scancode DROPBOMB);
	void Draw();
	void SpawnBomba(int i, int j, bool up, bool up2, bool down, bool down2, bool left, bool left2, bool right, bool right2);

};