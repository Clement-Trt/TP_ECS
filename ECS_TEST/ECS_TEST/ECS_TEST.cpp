#include <iostream>
#include "ecs.h"
#include "EntityTypes.h"

int main() {
    EntityManager entityManager;
    MovementSystem movementSystem;

    std::vector<EntityType*> entities;


    entities.push_back(entityManager.CreateNewEntityType());


    int baseType = EntityTypesEnum::BaseType;    
    entities.at(baseType)->AddComponent(0); // TransformComp
    entities.at(baseType)->AddComponent(1); // MeshComp
    entities.at(baseType)->AddComponent(2); // PositionComp
    entities.at(baseType)->AddComponent(3); // VelocityComp
    entities.at(baseType)->AddEntity();
    entities.at(baseType)->AddEntity();

    /*std::vector<Position> positions = { {0, 0}, {10, 10} };
    std::vector<Velocity> velocities = { {1, 1}, {2, -1} };*/

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            entities.at(0)->GetComponentList().at(i).at(j); // A envoyer dans une fonction update
        }
    }

    std::cout << "Entity ID 1: " << entities.at(0)->GetEntityID(1) <<"   YOUPLABOUM  " << std::endl;















    // Création d'entités
   /* EntityID e1 = entityManager.CreateEntity();
    EntityID e2 = entityManager.CreateEntity();*/
    
    //EntityManager::PNJs pnjs;

    // Stockage des composants
    /*std::vector<Position> positions = { {0, 0}, {10, 10} };
    std::vector<Velocity> velocities = { {1, 1}, {2, -1} };*/


    //std::vector<Transformable> transformables /*= { {1, 1}, {2, -1} }*/;

    // Mise à jour du système
    //float deltaTime = 0.16f; // Simulation 60 FPS
    //movementSystem.update(positions, velocities, deltaTime);

    //// Affichage des nouvelles positions
    //std::cout << "Entity 1: " << positions[0].x << ", " << positions[0].y << std::endl;
    //std::cout << "Entity 2: " << positions[1].x << ", " << positions[1].y << std::endl;

    return 0;
}
