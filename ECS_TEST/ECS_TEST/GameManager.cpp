//#include <iostream>
//#include "GameManager.h"
//
//void GameManager::Run()
//{
//
//	//sf::Clock clock; REMPLACER PAR SYSTEME DE TIMER
//	while (true) // REMPLACER PAR CONDITION DE FENETRE OUVERTE
//	{
//		SetDeltaTime(mDeltaTime); // CHANGER PAR SYSTEME DE TIMER
//
//		HandleInput(); // AJOUTER SYSTEME DE GESTION D'INPUT
//
//		Update();
//
//		Draw(); // AJOUTER SYSTEME DE DESSIN DIRECTX
//	}
//}
//
//void GameManager::Update()
//{
//	if (EM.GetEntityTab()[0] == nullptr)
//		return;
//
//	//mpScene->OnUpdate(); // RAJOUTER SCENE
//
//	// UPDATE
//	/*for (auto it = mEntities.begin(); it != mEntities.end(); )
//	{
//		Entity* entity = *it;
//
//		entity->Update();
//
//		if (entity->ToDestroy() == false)
//		{
//			++it;
//			continue;
//		}
//
//		mEntitiesToDestroy.push_back(entity);
//		it = mEntities.erase(it);
//	}*/
//
//	for (auto& entity : EM.GetEntityTab())
//	{
//		if (entity == nullptr)
//		{
//			break;
//		}
//
//
//		TransformComponent* transform = static_cast<TransformComponent*>(EM.GetComponentsTab()[entity->tab_index]->tab_components[Transform_index]);
//		MeshComponent* mesh = static_cast<MeshComponent*>(EM.GetComponentsTab()[entity->tab_index]->tab_components[Mesh_index]);
//		VelocityComponent* velocity = static_cast<VelocityComponent*>(EM.GetComponentsTab()[entity->tab_index]->tab_components[Velocity_index]);
//
//		std::cout << "\n ------------------------------------------------------------------------------------------- \n";
//		std::cout << "Entite " << entity->id << " position d'origine : ("
//			<< transform->m_transform.GetPositionX() << ", " << transform->m_transform.GetPositionY() << ")\n";
//
//
//		if (EM.HasComponent(entity, COMPONENT_TRANSFORM | COMPONENT_VELOCITY)) {
//
//			transform->m_transform.Move(0, velocity->vx, velocity->vy);
//
//			std::cout << "Entite " << entity->id << " nouvelle position: ("
//				<< transform->m_transform.GetPositionX() << ", " << transform->m_transform.GetPositionY() << ") avec : vx = " << velocity->vx << " et vy = " << velocity->vy << std::endl;
//		}
//		std::cout << "\n ------------------------------------------------------------------------------------------- \n";
//	}
//
//	// COLLISIONS
//
//	// DESTROY ENTITIES
//	//for (auto it = mEntitiesToDestroy.begin(); it != mEntitiesToDestroy.end(); ++it)
//	//{
//	//	delete* it;
//	//}
//
//	//mEntitiesToDestroy.clear();
//
//	//for (auto& entityToDestroy = EM.get)
//	// ADD ENTITIES
//	/*for (auto it = mEntitiesToAdd.begin(); it != mEntitiesToAdd.end(); ++it)
//	{
//		mEntities.push_back(*it);
//	}
//
//	mEntitiesToAdd.clear();*/
//}
//
//void GameManager::Draw()
//{
//	// AJOUTER SYSTEME DE DESSIN DIRECTX
//}
