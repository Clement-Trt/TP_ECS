#include "EntityManager.h"
#include <iostream>

Entity EntityManager::CreateEntity() {
	Entity entity = nextEntity++;
	entityComponents[entity] = COMPONENT_NONE;
	tab_entity[entity - 1] = entity; // ID entite commence a 1 alors que la premiere case du tableau est 0
	return entity;
}

void EntityManager::DestroyEntity(Entity entity, int index) {
	entityComponents.erase(entity);


	int lastIndex = nextEntity - 2;// nextEntity commence a 1 alors que la premiere case du tableau est 0, 
								   // mais a partir de 1 entite, nextEntity = taille de la table + 1 (ou lastIndex + 2)
	if (index < lastIndex) {
		tab_entity[index] = tab_entity[lastIndex];
		--nextEntity;
	}
	else {
		std::cerr << "Index invalide." << std::endl;
	}

}

void EntityManager::AddComponent(Entity entity, ComponentMask component) {
	entityComponents[entity] |= component;
}

void EntityManager::RemoveComponent(Entity entity, ComponentMask component) {
	entityComponents[entity] &= ~component;
}

bool EntityManager::HasComponent(Entity entity, ComponentMask component) const {
	auto it = entityComponents.find(entity);
	if (it != entityComponents.end()) {
		return (it->second & component) == component;
	}
	return false;
}


