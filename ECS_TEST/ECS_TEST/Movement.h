#pragma once

#include <memory>

#include "Components.h"
//#include "EntityManager.h"

//class EntityManager;
//class GameManager;

class Movement
{
protected:
	//std::unique_ptr<EntityManager> mEM = std::make_unique<EntityManager>();

	//GameManager* mGM;
	//EntityManager* mEM;

	//VelocityComponent* mVc;

public:

	void Initialize(/*GameManager* gameManager*/);

	void SetVelocity(VelocityComponent* vc, float velZ, float velX,float velY); // ou velFront, velRight, velUp ?
};

