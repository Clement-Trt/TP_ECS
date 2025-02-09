#pragma once

#include <vector>
#include <map>
#include "Components.h"
#include"pch.h"

enum EntityTypesEnum
{
	BaseType,

	Count
};



struct EntityType 
{
private:
	EntityID nextID = 0;

	std::vector<EntityID> entityIDs;

	std::vector<Component*> Components; // Contient un exemplaire de chaque component de ce type d'entite

	std::vector<std::vector<Component*>> ComponentsList; // Contient la liste de chaque pack de conteneur des entite

public:
	void AddEntity();
	void AddComponent(int componentIndex); // Ajoute le component (a l'index "componentIndex" de la liste de components generale) au vector Components

	EntityID& GetEntityID(int entityIndex) { return entityIDs.at(entityIndex); };
	std::vector<std::vector<Component*>>& GetComponentList() { return ComponentsList; };
};











	/*std::vector<Components::Position> positions;
	std::vector<Components::Velocity> velocities;*/


// Archetype pour les entités qui ont uniquement Velocity
/*struct ArchetypeVelocityOnly {
	std::vector<EntityID> entityIDs;
	std::vector<Velocity> velocities;
};*/
