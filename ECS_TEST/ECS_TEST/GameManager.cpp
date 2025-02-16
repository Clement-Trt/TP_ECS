#include "GameManager.h"

#include <iostream>
#include "EntityManager.h"
#include "Movement.h"
#include "Scene.h"

void GameManager::Initialize()
{
	mEM = new EntityManager();
	mMvmt = new Movement();
}

void GameManager::Run()
{
	mScene->Initialize();

	int i = 0;
	//sf::Clock clock; REMPLACER PAR SYSTEME DE TIMER
	while (i < 2) // REMPLACER PAR CONDITION DE FENETRE OUVERTE
	{
		//SetDeltaTime(mDeltaTime); // CHANGER PAR SYSTEME DE TIMER

		//HandleInput(); // AJOUTER SYSTEME DE GESTION D'INPUT

		Update();

		//Draw(); // AJOUTER SYSTEME DE DESSIN DIRECTX
		i++;
	}


}

void GameManager::Update()
{
	

	if (mEM->GetEntityTab()[0] != nullptr)
	{
		// Update
		mScene->Update();
		

		// COLLISIONS

	}


	// DESTROY ENTITIES
	for (auto& entityToDestroy : mEM->GetToDestroyTab())
	{
		mEM->DestroyEntity(entityToDestroy);
	}
	mEM->GetToDestroyTab().clear();

	// ADD ENTITIES
	for (auto& entityToAdd : mEM->GetEntityToAddTab())
	{
		mEM->AddEntityToTab(entityToAdd, mEM->GetComponentToAddTab()[entityToAdd->tab_index]);
	}
	mEM->GetEntityToAddTab().clear();
	mEM->ResetEntitiesToAdd();

}

void GameManager::Draw()
{
	// AJOUTER SYSTEME DE DESSIN DIRECTX
}
