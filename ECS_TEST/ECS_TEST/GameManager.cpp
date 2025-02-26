#include "GameManager.h"

#include <iostream>
#include "EntityManager.h"
#include "Movement.h"
#include "Scene.h"

void GameManager::Initialize(Scene* scene)
{
	mEM = new EntityManager();
	SetScene(scene);
	mScene->Initialize(this);
	mScene->OnInitialize();
}

void GameManager::Run()
{

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
		mScene->OnUpdate();
		

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
	mEM->GetComponentToAddTab().clear();
	mEM->ResetEntitiesToAdd();

}

void GameManager::Draw()
{
	// AJOUTER SYSTEME DE DESSIN DIRECTX
}
