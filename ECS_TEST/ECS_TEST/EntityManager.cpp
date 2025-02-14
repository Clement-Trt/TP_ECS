#include "EntityManager.h"
#include <iostream>

Entity* EntityManager::CreateEntity() {
	//Entity* entity = nextEntity++;
	Entity* entity = new Entity;
	entity->id = 1 + entityNb;
	entity->tab_index = entityNb;
	tab_entity[entity->id] = entity; // Ajout de l'entity dans le tableau d'entities

	EntityComponents* newComponents = new EntityComponents;

	newComponents->mask = COMPONENT_NONE;

	tab_CompEntities[entityNb] = newComponents; // Ajout des components (vides) de l'entity dans la case correspondant du tableau de composants
	// Pourquoi *newComponents et pas newComponents direct ?

	return entity;
}

void EntityManager::DestroyEntity(Entity* entity) {
	int index = entity->tab_index;
	int lastIndex = entityNb - 1;// nextEntity commence a 1 alors que la premiere case du tableau est 0, 
								   // mais a partir de 1 entite, nextEntity = taille de la table + 1 (ou lastIndex + 2)
	if (index < lastIndex) {
		tab_entity[index] = tab_entity[lastIndex];
		delete tab_entity[lastIndex];

		tab_CompEntities[index] = tab_CompEntities[lastIndex];
		delete tab_CompEntities[lastIndex];

		--entityNb;
	}
	else {
		std::cerr << "Index invalide." << std::endl;
	}
}

void EntityManager::AddComponent(Entity* entity, ComponentMask component) {
	tab_CompEntities[entity->tab_index]->mask |= component;
	//entityComponents[entity] |= component;
}

void EntityManager::RemoveComponent(Entity* entity, ComponentMask component) {
	tab_CompEntities[entity->tab_index]->mask &= ~component; 
	//entityComponents[entity] &= ~component;
}

bool EntityManager::HasComponent(Entity* entity, ComponentMask component) const {
	
	return (tab_CompEntities[entity->tab_index]->mask & component) == component;
	/*
	auto it = entityComponents.find(entity);
	if (it != entityComponents.end()) {
		return (it->second & component) == component;
	}
	return false;*/
}


