#include <iostream>
#include "EntityManager.h"
#include "Movement.h"


int main() {

	EntityManager EM;
	Movement movementManager;

	// Stockage des donnees des composants dans des maps
	std::unordered_map<Entity, Velocity> velocities;
	std::unordered_map<Entity, TRANSFORM> transforms;


	// Creation d'une entite
	Entity entity1 = EM.CreateEntity();
	Entity entity2 = EM.CreateEntity();
	Entity entity3 = EM.CreateEntity();

	// Ajout du composant Position a l'entite

	// Ajout du composant Velocity a l'entite
	EM.AddComponent(entity1, COMPONENT_VELOCITY);
	velocities[entity1] = { 1.0f, 1.5f };

	// Ajout du composant Velocity a l'entite
	EM.AddComponent(entity1, COMPONENT_TRANSFORM);

	// Ajout du composant Velocity a l'entite
	EM.AddComponent(entity2, COMPONENT_VELOCITY);
	velocities[entity2] = { 2.0f, 2.5f };

	// Ajout du composant Velocity a l'entite
	EM.AddComponent(entity2, COMPONENT_TRANSFORM);
	
	// Ajout du composant Velocity a l'entite
	EM.AddComponent(entity3, COMPONENT_VELOCITY);
	velocities[entity3] = { 5.0f, 5.0f };

	// Ajout du composant Velocity a l'entite
	EM.AddComponent(entity3, COMPONENT_TRANSFORM);

	int indexToDestroy = 1; // Pour gerer la destruction des entites dans le tableau de facon optimisee
	for (auto entity : EM.GetEntityTab())
	{
		std::cout << "BOB : "<< std::endl;
		if (entity == 0)
		{
			break; // break correct ici ?
		}
		std::cout << "\n ------------------------------------------------------------------------------------------- \n";
		std::cout << "Entite " << entity << " position d'origine : ("
			<< transforms[entity].GetPositionX() << ", " << transforms[entity].GetPositionY() << ")\n";

		// Systeme de mise a jour : pour chaque entite possedant Transform,
		// on met a jour sa position en fonction de sa velocite.
		if (EM.HasComponent(entity, COMPONENT_TRANSFORM) && EM.HasComponent(entity, COMPONENT_VELOCITY)) {

			TRANSFORM& transfo = transforms[entity];
			Velocity& vel = velocities[entity];

			// Mise a jour de la position
			transfo.Move(0, vel.vx, vel.vy);

			std::cout << "Entite " << entity << " nouvelle position: ("
				<< transforms[entity].GetPositionX() << ", " << transforms[entity].GetPositionY() << ")\n";
		}
		std::cout << "\n ------------------------------------------------------------------------------------------- \n";

		if (entity == entity2)
			EM.DestroyEntity(entity, indexToDestroy);

	}

	for (auto entity : EM.GetEntityTab())
	{
		if (entity == 0)
		{
			break; // break correct ici ?
		}
		std::cout << "\n\n ------------------------------------------------------------------------------------------- \n";
		std::cout << "Entity : " << entity << std::endl;
	}

	return 0;
}
