#pragma once

//#include "EntityManager.h"

class EntityManager;
class Scene;

class GameManager
{
protected:

	EntityManager* mEM;
	Scene* mScene;

	float mDeltaTime;

public:

	//GameManager();
	void Initialize();

	// __ Game loop __ 
	void Run();
	//void UpdatePhysics();
	void HandleInput();
	void Update();
	void Draw();

	void SetDeltaTime(float deltaTime) { mDeltaTime = deltaTime; }
	void SetScene(Scene* scene) { mScene = scene; }

	friend class Scene;
};

