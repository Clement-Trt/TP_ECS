#include <iostream>
#include "ecs.h"

int main() {
    ECS::EntityManager entityManager;
    ECS::MovementSystem movementSystem;

    // Création d'entités
    ECS::EntityID e1 = entityManager.createEntity();
    ECS::EntityID e2 = entityManager.createEntity();

    ECS::EntityManager::PNJs pnjs;

    // Stockage des composants
    std::vector<Components::Position> positions = { {0, 0}, {10, 10} };
    std::vector<Components::Velocity> velocities = { {1, 1}, {2, -1} };


    std::vector<Components::Transformable> transformables /*= { {1, 1}, {2, -1} }*/;

    // Mise à jour du système
    float deltaTime = 0.16f; // Simulation 60 FPS
    movementSystem.update(positions, velocities, deltaTime);

    // Affichage des nouvelles positions
    std::cout << "Entity 1: " << positions[0].x << ", " << positions[0].y << std::endl;
    std::cout << "Entity 2: " << positions[1].x << ", " << positions[1].y << std::endl;

    return 0;
}
