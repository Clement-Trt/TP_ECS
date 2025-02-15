#pragma once

class GameManager;
class EntityManager;

class Scene
{
protected:
	GameManager* mpGameManager;
	EntityManager* mpEntityManager;
public:

	//Scene();

	void Initialize();

	void Update();


	void SetGameManager(GameManager* pGameManager) { mpGameManager = pGameManager; }
	friend class GameManager;
};

