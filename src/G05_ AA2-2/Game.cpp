#pragma once
#include "Game.h"


Game::Game() {
	//puntero de tipo escena que controla menu y play y ranking
	gamestate = GameState::MENU;
	currentscene = new Menu();
}

Game::~Game()
{
}

void Game::LoopGame() {
	while (gamestate != GameState::EXIT) {
		if (currentscene->getState() == SceneState::RUNNING) {
			currentscene->EventHandler();
			currentscene->Update();
			currentscene->Draw();
		}
		else if (currentscene->getState() == SceneState::GOTOLVL1) {
			if (gamestate == GameState::MENU) {
				delete currentscene;
				gamestate = GameState::PLAY1;
				currentscene = new Play("PLAY1");
			}
		}
		else if (currentscene->getState() == SceneState::GOTOLVL2) {
			if (gamestate == GameState::MENU) {
				delete currentscene;
				gamestate = GameState::PLAY2;
				currentscene = new Play("PLAY2");
			}
		}
		else if (currentscene->getState() == SceneState::GOTORANKING) {
			if (gamestate == GameState::MENU) {
				delete currentscene;
				currentscene = new Ranking();
				gamestate = GameState::RANKING;
			}
		}
		else if (currentscene->getState() == SceneState::GOTOMENU) {
			if (gamestate == GameState::RANKING || gamestate == GameState::PLAY1 || gamestate == GameState::PLAY2) {
				delete currentscene;
				currentscene = new Menu();
				gamestate = GameState::MENU;
			}
		}
	}
}