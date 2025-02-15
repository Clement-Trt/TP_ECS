#include <iostream>
#include "EntityManager.h"
#include "Movement.h"


int main() {

	EntityManager* EM = new EntityManager();				 //			/!\/!\/!\/!\ A METTRE DANS GAME MANAGER /!\/!\/!\/!\/
	//MovementManager movementManager; //			/!\/!\/!\/!\ A METTRE DANS GAME MANAGER /!\/!\/!\/!\/


	// De ICI a ...

	Entity* entity1 = EM->CreateEntity();
	Entity* entity2 = EM->CreateEntity();
	Entity* entity3 = EM->CreateEntity();
	Entity* entity4 = EM->CreateEntity();


	std::cout << "Je suis la" << std::endl;
	EM->AddComponent(entity1, COMPONENT_VELOCITY);
	VelocityComponent* vc = static_cast<VelocityComponent*>(EM->GetComponentsTab()[entity1->tab_index]->tab_components[Velocity_index]);
	vc->vx = 1.0f;
	vc->vy = 1.5f;
	EM->AddComponent(entity1, COMPONENT_TRANSFORM);



	EM->AddComponent(entity2, COMPONENT_VELOCITY);
	vc = static_cast<VelocityComponent*>(EM->GetComponentsTab()[entity2->tab_index]->tab_components[Velocity_index]);
	vc->vx = 2.0f;
	vc->vy = 2.5f;
	EM->AddComponent(entity2, COMPONENT_TRANSFORM);



	EM->AddComponent(entity3, COMPONENT_VELOCITY);
	vc = static_cast<VelocityComponent*>(EM->GetComponentsTab()[entity3->tab_index]->tab_components[Velocity_index]);
	vc->vx = 5.0f;
	vc->vy = 5.5f;
	EM->AddComponent(entity3, COMPONENT_TRANSFORM);


	EM->AddComponent(entity4, COMPONENT_VELOCITY);
	vc = static_cast<VelocityComponent*>(EM->GetComponentsTab()[entity4->tab_index]->tab_components[Velocity_index]);
	vc->vx = 7.0f;
	vc->vy = 7.5f;
	EM->AddComponent(entity4, COMPONENT_TRANSFORM);
	std::cout << "vc.vx : " << vc->vx << "vc.vy : " << vc->vy << std::endl;

	int test = 0;
	for (; test < 2; test++)
	{
		//int indexToDestroy = 1; // Pour gerer la destruction des entites dans le tableau de facon optimisee
		for (auto entity : EM->GetEntityTab())
		{
			if (entity == nullptr)
			{
				break;
			}


			TransformComponent* transform = static_cast<TransformComponent*>(EM->GetComponentsTab()[entity->tab_index]->tab_components[Transform_index]);
			MeshComponent* mesh = static_cast<MeshComponent*>(EM->GetComponentsTab()[entity->tab_index]->tab_components[Mesh_index]);
			VelocityComponent* velocity = static_cast<VelocityComponent*>(EM->GetComponentsTab()[entity->tab_index]->tab_components[Velocity_index]);

			std::cout << "\n ------------------------------------------------------------------------------------------- \n";
			std::cout << "Entite " << entity->id << " position d'origine : ("
				<< transform->m_transform.GetPositionX() << ", " << transform->m_transform.GetPositionY() << ")\n";


			if (EM->HasComponent(entity, COMPONENT_TRANSFORM | COMPONENT_VELOCITY)) {

				transform->m_transform.Move(0, velocity->vx, velocity->vy);

				std::cout << "Entite " << entity->id << " nouvelle position: ("
					<< transform->m_transform.GetPositionX() << ", " << transform->m_transform.GetPositionY() << ") avec : vx = " << velocity->vx << " et vy = " << velocity->vy << std::endl;
			}
			std::cout << "\n ------------------------------------------------------------------------------------------- \n";

			if (test == 0 && entity == entity3)
			{
				EM->DestroyEntity(entity);
				entity4 = EM->GetEntityTab()[entity->tab_index]; //			/!\/!\/!\/!\ A METTRE DANS GAME MANAGER /!\/!\/!\/!\/
				entity = EM->GetEntityTab()[EM->GetNbEntity() - 1];
			}
		}
	}

	for (auto entity : EM->GetEntityTab())
	{
		if (entity == nullptr)
		{
			break;
		}
		std::cout << "\n\n ------------------------------------------------------------------------------------------- \n";
		std::cout << "Entity : " << entity->id << std::endl;
	}

	// ICI :  			/!\/!\/!\/!\ A METTRE DANS SCENE /!\/!\/!\/!\/
	return 0;
}
