#pragma once
#include "Player.h"


Player::Player() {
	PlayerPath = "../../res/img/player1.png";
	Player_ID = PLAYER1_SPRITE;
	Renderer::Instance()->LoadTexture(Player_ID, PlayerPath);
	Renderer::Instance()->GetTextureSize(Player_ID);
	PlayerPositionXY = { 0, 0 };
	frameWidth = textWidth / 3;
	frameHeight = textHeight / 4;
	Player_Position.x = PlayerPositionXY.x;
	Player_Position.y = PlayerPositionXY.y;
	Player_Rect.x = 0;
	Player_Rect.y = 0;
	Player_Position.h = LADO_CASILLA;
	Player_Rect.h = frameHeight;
	Player_Position.w = LADO_CASILLA;
	Player_Rect.w = frameWidth;
	frameTime = 0;
	lifes = 3;
	score = 0;
	bomb = Bomb();
}


Player::~Player()
{
}

void Player::EventHandler(SDL_Event evento) {
	switch (evento.type) {
	default:
		break;
	}
}

Key Player::Movement(SDL_Scancode UP, SDL_Scancode DOWN, SDL_Scancode LEFT, SDL_Scancode RIGHT, SDL_Scancode DROPBOMB) {
	//std::cout << Player_Position.x << " " << Player_Position.y << std::endl;
	frameTime++;
	if (FPS / frameTime <= 5) {
		frameTime = 0;
		if (Player_Rect.x == 48 * 2)
			cambiop = -1;
		else if (Player_Rect.x == 0)
			cambiop = 1;
		Player_Rect.x += 48 * cambiop;
	}



	//Movimiento
	const Uint8 *keyboardstate = SDL_GetKeyboardState(NULL);
	//EL BOOSTEO DE LOS PATINES ES FUNCIONAL PERO COMO NO PODEMOS ROMPER LADRILLOS NO PODEMOS CARGAR POWER-UPS NO SE ACTIVAN.

	if (!dropbomb) {
		if (keyboardstate[DROPBOMB]) {
			bomb.lastTime = clock();
			bomb.timeDown = 3.;
			bomb.deltaTime = 0;
			std::cout << "drop bomb" << std::endl;
			return Key::BOMB;
		}
	}

	if (keyboardstate[UP]) {
		return Key::UP;
	}
	else if (keyboardstate[DOWN]) {
		return Key::DOWN;
	}
	else if (keyboardstate[LEFT]) {
		return Key::LEFT;
	}
	else if (keyboardstate[RIGHT]) {
		return Key::RIGHT;
	}
	else {
		return Key::NONE;
	}


	//Daño
	//ESTO DEBERÍA COMPROBAR SI EN LA POSICIÓN DE LA ONDA EXPANSIVA HAY UN PLAYER Y EN CASO AFIRMATIVO LE QUITA VIDA PERO NO VA.
	//if (bomba.explotando) {
	//	std::cout << "pupita" << std::endl;
	//	if (lvl.tablero[tmpPosXY.x][tmpPosXY.y] == lvl.tablero[bomba.Explosion1_Position.x][bomba.Explosion1_Position.y] ||
	//		lvl.tablero[tmpPosXY.x][tmpPosXY.y] == lvl.tablero[bomba.Explosion2_Position.x][bomba.Explosion2_Position.y] ||
	//		lvl.tablero[tmpPosXY.x][tmpPosXY.y] == lvl.tablero[bomba.Explosion3_Position.x][bomba.Explosion3_Position.y] ||
	//		lvl.tablero[tmpPosXY.x][tmpPosXY.y] == lvl.tablero[bomba.Explosion4_Position.x][bomba.Explosion4_Position.y] ||
	//		lvl.tablero[tmpPosXY.x][tmpPosXY.y] == lvl.tablero[bomba.Explosion5_Position.x][bomba.Explosion5_Position.y] ||
	//		lvl.tablero[tmpPosXY.x][tmpPosXY.y] == lvl.tablero[bomba.Explosion6_Position.x][bomba.Explosion6_Position.y] ||
	//		lvl.tablero[tmpPosXY.x][tmpPosXY.y] == lvl.tablero[bomba.Explosion7_Position.x][bomba.Explosion7_Position.y] ||
	//		lvl.tablero[tmpPosXY.x][tmpPosXY.y] == lvl.tablero[bomba.Explosion8_Position.x][bomba.Explosion8_Position.y]) {
	//		lifes--;
	//		std::cout << lifes << std::endl;
	//	}
	//}
}
void Player::Draw() {
	if (dropbomb) {
		//ESTO DEBERÍA COMPROBAR SI EN LA POSICIÓN DE LA ONDA EXPANSIVA HAY UN LADRILLO PERO NO VA.
		//if (lvl.tablero[posicionBomba.x][posicionBomba.y + 1] == casillas::INDESTRUCTIBLE_WALL && lvl.tablero[posicionBomba.x][posicionBomba.y + 1] == casillas::DESTRUCTIBLE_WALL)
		//{ down = true; }
		//else 
		//{ down = false; }

		//if (lvl.tablero[posicionBomba.x][posicionBomba.y + 2] == casillas::INDESTRUCTIBLE_WALL && lvl.tablero[posicionBomba.x][posicionBomba.y + 2] == casillas::DESTRUCTIBLE_WALL)
		//{ down2 = true; }
		//else 
		//{ down2 = false; }

		//if (lvl.tablero[posicionBomba.x][posicionBomba.y - 1] == casillas::INDESTRUCTIBLE_WALL && lvl.tablero[posicionBomba.x][posicionBomba.y - 1] == casillas::DESTRUCTIBLE_WALL)
		//{ up = true; }
		//else 
		//{ up = false; }

		//if (lvl.tablero[posicionBomba.x][posicionBomba.y - 2] == casillas::INDESTRUCTIBLE_WALL && lvl.tablero[posicionBomba.x][posicionBomba.y - 2] == casillas::DESTRUCTIBLE_WALL)
		//{ up2 = true; }
		//else 
		//{ up2 = false; }

		//if (lvl.tablero[posicionBomba.x][posicionBomba.x + 1] == casillas::INDESTRUCTIBLE_WALL && lvl.tablero[posicionBomba.x][posicionBomba.x + 1] == casillas::DESTRUCTIBLE_WALL)
		//{ right = true; }
		//else 
		//{ right = false; }

		//if (lvl.tablero[posicionBomba.x][posicionBomba.x + 2] == casillas::INDESTRUCTIBLE_WALL && lvl.tablero[posicionBomba.x][posicionBomba.x + 2] == casillas::DESTRUCTIBLE_WALL)
		//{ right2 = true; }
		//else 
		//{ right2 = false; }

		//if (lvl.tablero[posicionBomba.x][posicionBomba.x - 1] == casillas::INDESTRUCTIBLE_WALL && lvl.tablero[posicionBomba.x][posicionBomba.x - 1] == casillas::DESTRUCTIBLE_WALL)
		//{ left = true; }
		//else 
		//{ left = false; }

		//if (lvl.tablero[posicionBomba.x][posicionBomba.x - 2] == casillas::INDESTRUCTIBLE_WALL && lvl.tablero[posicionBomba.x][posicionBomba.x - 2] == casillas::DESTRUCTIBLE_WALL)
		//{ left2 = true; }
		//else 
		//{ left2 = true; }
		Player::SpawnBomba(BombPosition.x, BombPosition.y, up, up2, down, down2, left, left2, right, right2);
		std::cout << BombPosition.x << " " << BombPosition.y << std::endl;

	}
	if (bomb.explosion) {
		bomb.lastTime = clock();
		bomb.timeDown = 3.;
		bomb.deltaTime = 0;
		dropbomb = false;
		bomb.explosion = false;
	}
	Renderer::Instance()->PushSprite(Player_ID, Player_Rect, Player_Position);
}

void Player::SpawnBomba(int i, int j, bool up, bool up2, bool down, bool down2, bool left, bool left2, bool right, bool right2) {
	bomb.Draw(i, j, up, up2, down, down2, left, left2, right, right2);
	bomb.Update();
}