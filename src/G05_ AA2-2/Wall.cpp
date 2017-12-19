#pragma once
#include "Wall.h"
#include "Constants.h"



Wall::Wall()
{
	WallPath = "../../res/img/items.png";
	Wall_ID = INDESTRUCTIBLE_WALL;
	Renderer::Instance()->LoadTexture(Wall_ID, WallPath);
	Renderer::Instance()->GetTextureSize(Wall_ID);
	frameWidth = (textWidth / 3);
	frameHeight = (textHeight / 2);
	Wall_Position.x = 0;
	Wall_Position.y = 0;
	Wall_Rect.x = 0;
	Wall_Rect.y = 0;
	Wall_Position.h = 48;
	Wall_Rect.h = frameHeight;
	Wall_Position.w = 48;
	Wall_Rect.w = frameWidth;
}


Wall::~Wall()
{
}

void::Wall::setup() {

}

void Wall::draw(std::string wall_ID, int i, int j)
{
	Wall_Position.x = i;
	Wall_Position.y = j;
	Renderer::Instance()->PushSprite(Wall_ID, Wall_Rect, Wall_Position);
	//ESTO ES MÁS LÓGICA QUE CÓDIGO Y ES UNA VERSIÓN SIMPLIFICADA DE LO QUE PASARÍA AL DESTRUIR UN BLOQUE.
	//if (wall_ID == DESTRUCTIBLE_WALL) {
	//	if (explosion_range.position == Wall_Position) {
	//		if (rand() % 100<probability_PU) {
	//			if (rand() % 2 == 1) {
	//				PU.helmet = true;
	//			}
	//			else {
	//				PU.rollers = true;
	//			}
	//		}
	//	}
	//}
}

void Wall::update()
{

}
