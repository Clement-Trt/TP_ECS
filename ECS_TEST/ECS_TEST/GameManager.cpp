#include <iostream>
#include "EntityManager.h"
#include "GameManager.h"
#include "Scene.h"

void GameManager::Initialize()
{
	mEM = new EntityManager();
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
	/*Entity* entity1 = mEM->CreateEntity();
	Entity* entity2 = mEM->CreateEntity();
	Entity* entity3 = mEM->CreateEntity();
	Entity* entity4 = mEM->CreateEntity();*/


		/*mEM->AddComponent(entity1, COMPONENT_VELOCITY);
		VelocityComponent* vc = static_cast<VelocityComponent*>(mEM->GetComponentsTab()[entity1->tab_index]->tab_components[Velocity_index]);
		vc->vx = 1.0f;
		vc->vy = 1.5f;
		mEM->AddComponent(entity1, COMPONENT_TRANSFORM);



		mEM->AddComponent(entity2, COMPONENT_VELOCITY);
		vc = static_cast<VelocityComponent*>(mEM->GetComponentsTab()[entity2->tab_index]->tab_components[Velocity_index]);
		vc->vx = 2.0f;
		vc->vy = 2.5f;
		mEM->AddComponent(entity2, COMPONENT_TRANSFORM);



		mEM->AddComponent(entity3, COMPONENT_VELOCITY);
		vc = static_cast<VelocityComponent*>(mEM->GetComponentsTab()[entity3->tab_index]->tab_components[Velocity_index]);
		vc->vx = 5.0f;
		vc->vy = 5.5f;
		mEM->AddComponent(entity3, COMPONENT_TRANSFORM);


		mEM->AddComponent(entity4, COMPONENT_VELOCITY);
		vc = static_cast<VelocityComponent*>(mEM->GetComponentsTab()[entity4->tab_index]->tab_components[Velocity_index]);
		vc->vx = 7.0f;
		vc->vy = 7.5f;
		mEM->AddComponent(entity4, COMPONENT_TRANSFORM);*/

		/*if (mEM->GetEntityTab()[0] == nullptr)
			return;*/

			//mpScene->OnUpdate(); // RAJOUTER SCENE

			// UPDATE
			/*for (auto it = mEntities.begin(); it != mEntities.end(); )
			{
				Entity* entity = *it;

				entity->Update();

				if (entity->ToDestroy() == false)
				{
					++it;
					continue;
				}

				mEntitiesToDestroy.push_back(entity);
				it = mEntities.erase(it);
			}*/

	if (mEM->GetEntityTab()[0] != nullptr)
	{
		mScene->Update();
		/*for (auto& entity : mEM->GetEntityTab())
		{
			if (entity == nullptr)
			{
				break;
			}


			TransformComponent* transform = static_cast<TransformComponent*>(mEM->GetComponentsTab()[entity->tab_index]->tab_components[Transform_index]);
			MeshComponent* mesh = static_cast<MeshComponent*>(mEM->GetComponentsTab()[entity->tab_index]->tab_components[Mesh_index]);
			VelocityComponent* velocity = static_cast<VelocityComponent*>(mEM->GetComponentsTab()[entity->tab_index]->tab_components[Velocity_index]);

			std::cout << "\n ------------------------------------------------------------------------------------------- \n";
			std::cout << "Entite " << entity->id << " position d'origine : ("
				<< transform->m_transform.GetPositionX() << ", " << transform->m_transform.GetPositionY() << ")\n";


			if (mEM->HasComponent(entity, COMPONENT_TRANSFORM | COMPONENT_VELOCITY)) {

				transform->m_transform.Move(0, velocity->vx, velocity->vy);

				std::cout << "Entite " << entity->id << " nouvelle position: ("
					<< transform->m_transform.GetPositionX() << ", " << transform->m_transform.GetPositionY() << ") avec : vx = " << velocity->vx << " et vy = " << velocity->vy << std::endl;
			}
			std::cout << "\n ------------------------------------------------------------------------------------------- \n";
		}

		for (auto entity : mEM->GetEntityTab())
		{
			if (entity == nullptr)
			{
				break;
			}
			std::cout << "\n\n ------------------------------------------------------------------------------------------- \n";
			std::cout << "Entity : " << entity->id << std::endl;
		}*/




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
