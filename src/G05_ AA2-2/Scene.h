#pragma once
#include "Types.h"

class Scene {

protected:
	SceneState scenestate;


public:
	Scene();
	~Scene();

	virtual void EventHandler() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	SceneState getState();
};

