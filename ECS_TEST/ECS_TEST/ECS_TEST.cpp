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


	for (auto entity : EM.GetEntityTab())
	{
		if (entity != 0)
		{
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
		}
	}

	return 0;


























	// Creation d'entites
   /* EntityID e1 = entityManager.CreateEntity();
	EntityID e2 = entityManager.CreateEntity();*/

	//EntityManager::PNJs pnjs;

	// Stockage des composants
	/*std::vector<Position> positions = { {0, 0}, {10, 10} };
	std::vector<Velocity> velocities = { {1, 1}, {2, -1} };*/


	//std::vector<Transformable> transformables /*= { {1, 1}, {2, -1} }*/;

	// Mise a jour du systeme
	//float deltaTime = 0.16f; // Simulation 60 FPS
	//movementSystem.update(positions, velocities, deltaTime);

	//// Affichage des nouvelles positions
	//std::cout << "Entity 1: " << positions[0].x << ", " << positions[0].y << std::endl;
	//std::cout << "Entity 2: " << positions[1].x << ", " << positions[1].y << std::endl;

	//return 0;
}
