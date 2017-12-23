#include "Bomb.h"



Bomb::Bomb()
{
	//Cargamos las imágenes de bombas y explosión.
	BombasPath = "../../res/img/items.png";
	ExplosionPath = "../../res/img/explosion.png";
	//Les damos una ID.
	Bombas_ID = BOMB;
	Explosion_ID1 = EXPLOSION1;
	Explosion_ID2 = EXPLOSION2;
	Explosion_ID3 = EXPLOSION3;
	Explosion_ID4 = EXPLOSION4;
	Explosion_ID5 = EXPLOSION5;
	Explosion_ID6 = EXPLOSION6;
	Explosion_ID7 = EXPLOSION7;
	Explosion_ID8 = EXPLOSION8;
	Explosion_ID = EXPLOSION;
	//Cargamos las texturas.
	Renderer::Instance()->LoadTexture(Bombas_ID, BombasPath);
	Renderer::Instance()->GetTextureSize(Bombas_ID);
	Renderer::Instance()->LoadTexture(Explosion_ID, ExplosionPath);
	Renderer::Instance()->GetTextureSize(Explosion_ID);
	Renderer::Instance()->LoadTexture(Explosion_ID1, ExplosionPath);
	Renderer::Instance()->GetTextureSize(Explosion_ID1);
	Renderer::Instance()->LoadTexture(Explosion_ID2, ExplosionPath);
	Renderer::Instance()->GetTextureSize(Explosion_ID2);
	Renderer::Instance()->LoadTexture(Explosion_ID3, ExplosionPath);
	Renderer::Instance()->GetTextureSize(Explosion_ID3);
	Renderer::Instance()->LoadTexture(Explosion_ID4, ExplosionPath);
	Renderer::Instance()->GetTextureSize(Explosion_ID4);
	Renderer::Instance()->LoadTexture(Explosion_ID5, ExplosionPath);
	Renderer::Instance()->GetTextureSize(Explosion_ID5);
	Renderer::Instance()->LoadTexture(Explosion_ID6, ExplosionPath);
	Renderer::Instance()->GetTextureSize(Explosion_ID6);
	Renderer::Instance()->LoadTexture(Explosion_ID7, ExplosionPath);
	Renderer::Instance()->GetTextureSize(Explosion_ID7);
	Renderer::Instance()->LoadTexture(Explosion_ID8, ExplosionPath);
	Renderer::Instance()->GetTextureSize(Explosion_ID8);

	//Les damos unos valores a los distintos atributos de las bombas y las explosiones.

	//BOMB
	frameWidth = textWidth / 3;
	frameHeight = textHeight / 2;
	tmpPosXY;
	Bombas_Rect.x = 0;
	Bombas_Rect.y = frameHeight;
	Bombas_Position.h = 48;
	Bombas_Rect.h = frameHeight;
	Bombas_Position.w = 48;
	Bombas_Rect.w = frameWidth;

	//EXPLOSION
	Explosion_Position.x = 0;
	Explosion_Position.y = 0;
	Explosion_Rect.x = 0;
	Explosion_Rect.y = 0;
	Explosion_Position.h = 48;
	Explosion_Rect.h = frameHeight;
	Explosion_Position.w = 48;
	Explosion_Rect.w = frameWidth;
	lastTime = clock();
	timeDown = 5.;
	deltaTime = 0;
	explosion = false;
	//explosion arriba1
	Explosion1_Position.x = 0;
	Explosion1_Position.y = Bombas_Position.x + frameWidth * 2;
	Explosion1_Rect.x = 0;
	Explosion1_Rect.y = Bombas_Position.x + frameWidth * 2;
	Explosion1_Position.h = 48;
	Explosion1_Rect.h = frameHeight;
	Explosion1_Position.w = 48;
	Explosion1_Rect.w = frameWidth;
	//explosion arriba2
	Explosion2_Position.x = 0;
	Explosion2_Position.y = 100;
	Explosion2_Rect.x = 0;
	Explosion2_Rect.y = 0;
	Explosion2_Position.h = 48;
	Explosion2_Rect.h = frameHeight;
	Explosion2_Position.w = 48;
	Explosion2_Rect.w = frameWidth;
	//explosion dedrecha1
	Explosion3_Position.x = 0;
	Explosion3_Position.y = 200;
	Explosion3_Rect.x = 0;
	Explosion3_Rect.y = 0;
	Explosion3_Position.h = 48;
	Explosion3_Rect.h = frameHeight;
	Explosion3_Position.w = 48;
	Explosion3_Rect.w = frameWidth;
	//explosion derecha2
	Explosion4_Position.x = 0;
	Explosion4_Position.y = 300;
	Explosion4_Rect.x = 0;
	Explosion4_Rect.y = 0;
	Explosion4_Position.h = 48;
	Explosion4_Rect.h = frameHeight;
	Explosion4_Position.w = 48;
	Explosion4_Rect.w = frameWidth;
	//explosion izquierda1
	Explosion5_Position.x = 0;
	Explosion5_Position.y = 400;
	Explosion5_Rect.x = 0;
	Explosion5_Rect.y = 0;
	Explosion5_Position.h = 48;
	Explosion5_Rect.h = frameHeight;
	Explosion5_Position.w = 48;
	Explosion5_Rect.w = frameWidth;
	//explosion izquierda2
	Explosion6_Position.x = 0;
	Explosion6_Position.y = 500;
	Explosion6_Rect.x = 0;
	Explosion6_Rect.y = 0;
	Explosion6_Position.h = 48;
	Explosion6_Rect.h = frameHeight;
	Explosion6_Position.w = 48;
	Explosion6_Rect.w = frameWidth;
	//explosion abajo1
	Explosion7_Position.x = 0;
	Explosion7_Position.y = 600;
	Explosion7_Rect.x = 0;
	Explosion7_Rect.y = 0;
	Explosion7_Position.h = 48;
	Explosion7_Rect.h = frameHeight;
	Explosion7_Position.w = 48;
	Explosion7_Rect.w = frameWidth;
	//explosion abajo2
	Explosion8_Position.x = 0;
	Explosion8_Position.y = 700;
	Explosion8_Rect.x = 0;
	Explosion8_Rect.y = 0;
	Explosion8_Position.h = 48;
	Explosion8_Rect.h = frameHeight;
	Explosion8_Position.w = 48;
	Explosion8_Rect.w = frameWidth;
}


Bomb::~Bomb() {
}

void Bomb::Update() {
	//tmpPosXY = CoordenadaACasilla(Bombas_Position.x, Bombas_Position.y);
	if (timeDown > 0) {
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime;
		//std::cout << timeDown << std::endl;
		if (timeDown <= 0) {
			//std::cout << "destruir bomba" << std::endl;
			explosion = true;
			explotando = false;
		}
	}

}

void Bomb::Draw(int i, int j, bool up, bool up2, bool down, bool down2, bool left, bool left2, bool right, bool right2) {
	Bombas_Position.x = i;
	Bombas_Position.y = j;
	if (timeDown >= 0) {
		if (timeDown > 1) {
			Renderer::Instance()->PushSprite(Bombas_ID, Bombas_Rect, Bombas_Position);
		}
		else if (timeDown <= 1) {
			explotando = true;
			//std::cout << "Deberia salir la explosion" << std::endl;
			//Bomba0
			Explosion_Position.x = Bombas_Position.x;
			Explosion_Position.y = Bombas_Position.y;
			Explosion_Rect.x = frameWidth * 2;
			Explosion_Rect.y = 0;
			Explosion_Position.h = 48;
			Explosion_Rect.h = frameHeight;
			Explosion_Position.w = 48;
			Explosion_Rect.w = frameWidth;
			Renderer::Instance()->PushSprite(Explosion_ID, Explosion_Rect, Explosion_Position);

			if (!up) {
				//Bomba1 = arriba 1
				Explosion1_Position.x = Bombas_Position.x;
				Explosion1_Position.y = Bombas_Position.y - LADO_CASILLA * 1;
				Explosion1_Rect.x = frameWidth * 2;
				Explosion1_Rect.y = frameWidth * 6;
				Explosion1_Position.h = 48;
				Explosion1_Rect.h = frameHeight;
				Explosion1_Position.w = 48;
				Explosion1_Rect.w = frameWidth;
				Renderer::Instance()->PushSprite(Explosion_ID1, Explosion1_Rect, Explosion1_Position);
			}
			if (!up2) {
				//Bomba2 = arriba 2
				Explosion2_Position.x = Bombas_Position.x;
				Explosion2_Position.y = Bombas_Position.y - LADO_CASILLA * 2;
				Explosion2_Rect.x = frameWidth * 2;
				Explosion2_Rect.y = frameWidth * 3;
				Explosion2_Position.h = 48;
				Explosion2_Rect.h = frameHeight;
				Explosion2_Position.w = 48;
				Explosion2_Rect.w = frameWidth;
				Renderer::Instance()->PushSprite(Explosion_ID2, Explosion2_Rect, Explosion2_Position);
			}
			if (!right) {
				//Bomba3 = derecha 1
				Explosion3_Position.x = Bombas_Position.x + LADO_CASILLA;
				Explosion3_Position.y = Bombas_Position.y;
				Explosion3_Rect.x = frameWidth * 2;
				Explosion3_Rect.y = frameWidth * 5;
				Explosion3_Position.h = 48;
				Explosion3_Rect.h = frameHeight;
				Explosion3_Position.w = 48;
				Explosion3_Rect.w = frameWidth;
				Renderer::Instance()->PushSprite(Explosion_ID3, Explosion3_Rect, Explosion3_Position);
			}
			if (!right2) {
				//Bomba4 = derecha 2
				Explosion4_Position.x = Bombas_Position.x + LADO_CASILLA * 2;
				Explosion4_Position.y = Bombas_Position.y;
				Explosion4_Rect.x = frameWidth * 2;
				Explosion4_Rect.y = frameWidth * 2;
				Explosion4_Position.h = 48;
				Explosion4_Rect.h = frameHeight;
				Explosion4_Position.w = 48;
				Explosion4_Rect.w = frameWidth;
				Renderer::Instance()->PushSprite(Explosion_ID4, Explosion4_Rect, Explosion4_Position);
			}
			if (!left) {
				//Bomba5 = izquierda 1
				Explosion5_Position.x = Bombas_Position.x - LADO_CASILLA;
				Explosion5_Position.y = Bombas_Position.y;
				Explosion5_Rect.x = frameWidth * 2;
				Explosion5_Rect.y = frameWidth * 5;
				Explosion5_Position.h = 48;
				Explosion5_Rect.h = frameHeight;
				Explosion5_Position.w = 48;
				Explosion5_Rect.w = frameWidth;
				Renderer::Instance()->PushSprite(Explosion_ID5, Explosion5_Rect, Explosion5_Position);
			}
			if (!left2) {
				//Bomba5 = izquierda 2
				Explosion6_Position.x = Bombas_Position.x - LADO_CASILLA * 2;
				Explosion6_Position.y = Bombas_Position.y;
				Explosion6_Rect.x = frameWidth * 2;;
				Explosion6_Rect.y = frameWidth * 1;
				Explosion6_Position.h = 48;
				Explosion6_Rect.h = frameHeight;
				Explosion6_Position.w = 48;
				Explosion6_Rect.w = frameWidth;
				Renderer::Instance()->PushSprite(Explosion_ID6, Explosion6_Rect, Explosion6_Position);
			}
			if (!down) {
				//Bomba7 = abajo 1
				Explosion7_Position.x = Bombas_Position.x;
				Explosion7_Position.y = Bombas_Position.y + LADO_CASILLA * 1;
				Explosion7_Rect.x = frameWidth * 2;
				Explosion7_Rect.y = frameWidth * 6;
				Explosion7_Position.h = 48;
				Explosion7_Rect.h = frameHeight;
				Explosion7_Position.w = 48;
				Explosion7_Rect.w = frameWidth;
				Renderer::Instance()->PushSprite(Explosion_ID7, Explosion7_Rect, Explosion7_Position);
			}
			if (!down2) {
				//Bomba7 = abajo 2
				Explosion8_Position.x = Bombas_Position.x;
				Explosion8_Position.y = Bombas_Position.y + LADO_CASILLA * 2;
				Explosion8_Rect.x = frameWidth * 2;
				Explosion8_Rect.y = frameWidth * 4;
				Explosion8_Position.h = 48;
				Explosion8_Rect.h = frameHeight;
				Explosion8_Position.w = 48;
				Explosion8_Rect.w = frameWidth;
				Renderer::Instance()->PushSprite(Explosion_ID8, Explosion8_Rect, Explosion8_Position);
			}



		}
	}
}