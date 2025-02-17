
#include <iostream>
#include "Scene.h"
#include "EntityManager.h"
#include "GameManager.h"
#include "Movement.h"

void Scene::Initialize()
{
	mpEntityManager = mpGameManager->mEM;

	mMvmt = new Movement;
	mMvmt->Initialize(mpGameManager);

	Entity* entity1 = mpEntityManager->CreateEntity();
	Entity* entity2 = mpEntityManager->CreateEntity();
	Entity* entity3 = mpEntityManager->CreateEntity();
	Entity* entity4 = mpEntityManager->CreateEntity();

	mpEntityManager->AddComponent(entity1, COMPONENT_VELOCITY | COMPONENT_TRANSFORM);

	mMvmt->SetVelocity(entity1, 1.0, 1.0, 1.5);
	/*VelocityComponent* vc = static_cast<VelocityComponent*>(mpEntityManager->GetComponentToAddTab()[0]->tab_components[Velocity_index]);
	
	vc->vx = 1.0f;
	vc->vy = 1.5f;*/
	//mpEntityManager->AddComponent(entity1, COMPONENT_TRANSFORM);



	mpEntityManager->AddComponent(entity2, COMPONENT_VELOCITY | COMPONENT_TRANSFORM);
	mMvmt->SetVelocity(entity2, 1.0, 2.0, 2.5);
	/*vc = static_cast<VelocityComponent*>(mpEntityManager->GetComponentToAddTab()[1]->tab_components[Velocity_index]);
	vc->vx = 2.0f;
	vc->vy = 2.5f;*/
	//mpEntityManager->AddComponent(entity2, COMPONENT_TRANSFORM);
	//mpEntityManager->RemoveComponent(entity2, COMPONENT_VELOCITY);


	mpEntityManager->AddComponent(entity3, COMPONENT_VELOCITY | COMPONENT_TRANSFORM);
	mMvmt->SetVelocity(entity3, 1.0, 5.0, 5.5);
	/*vc = static_cast<VelocityComponent*>(mpEntityManager->GetComponentToAddTab()[2]->tab_components[Velocity_index]);
	vc->vx = 5.0f;
	vc->vy = 5.5f;*/
	//mpEntityManager->AddComponent(entity3, COMPONENT_TRANSFORM);



	mpEntityManager->AddComponent(entity4, COMPONENT_VELOCITY | COMPONENT_TRANSFORM);
	mMvmt->SetVelocity(entity4, 1.0, 7.0, 7.5);
	//vc = static_cast<VelocityComponent*>(mpEntityManager->GetComponentToAddTab()[3]->tab_components[Velocity_index]);
	//vc->vx = 7.0f;
	//vc->vy = 7.5f;
	//mpEntityManager->AddComponent(entity4, COMPONENT_TRANSFORM);
}

void Scene::Update()
{
	for (auto& entity : mpEntityManager->GetEntityTab())
	{
		if (entity == nullptr)
		{
			break;
		}


		TransformComponent* transform = static_cast<TransformComponent*>(mpEntityManager->GetComponentsTab()[entity->tab_index]->tab_components[Transform_index]);
		MeshComponent* mesh = static_cast<MeshComponent*>(mpEntityManager->GetComponentsTab()[entity->tab_index]->tab_components[Mesh_index]);
		VelocityComponent* velocity = static_cast<VelocityComponent*>(mpEntityManager->GetComponentsTab()[entity->tab_index]->tab_components[Velocity_index]);

		std::cout << "\n ------------------------------------------------------------------------------------------- \n";
		std::cout << "Entite " << entity->id << " position d'origine : ("
			<< transform->m_transform.GetPositionX() << ", " << transform->m_transform.GetPositionY() << ")\n";


		if (mpEntityManager->HasComponent(entity, COMPONENT_TRANSFORM | COMPONENT_VELOCITY)) {

			transform->m_transform.Move(velocity->vz, velocity->vx, velocity->vy);

			std::cout << "Entite " << entity->id << " nouvelle position: ("
				<< transform->m_transform.GetPositionX() << ", " << transform->m_transform.GetPositionY() << ") avec : vx = " << velocity->vx << " et vy = " << velocity->vy << std::endl;
		}
		std::cout << "\n ------------------------------------------------------------------------------------------- \n";
	}

	for (auto entity : mpEntityManager->GetEntityTab())
	{
		if (entity == nullptr)
		{
			break;
		}
		std::cout << "\n\n ------------------------------------------------------------------------------------------- \n";
		std::cout << "Entity : " << entity->id << std::endl;
	}
}

void Scene::Close()
{
	
}
