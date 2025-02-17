#pragma once

class GameManager;
class EntityManager;
class Movement;

class Scene
{
protected:
	GameManager* mpGameManager;
	EntityManager* mpEntityManager;

	Movement* mMvmt;
public:

	//Scene();

	void Initialize();

	void Update();

	void Close();


	void SetGameManager(GameManager* pGameManager) { mpGameManager = pGameManager; }
	friend class GameManager;
};

