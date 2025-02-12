#include "EntityManager.h"


Entity EntityManager::CreateEntity() {
    Entity entity = nextEntity++;
    entityComponents[entity] = COMPONENT_NONE;
    tab_entity[entity] = entity;
    return entity;
}

void EntityManager::DestroyEntity(Entity entity) {
    entityComponents.erase(entity);
    // Vous pouvez egalement supprimer les donnees de composants associees ailleurs
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


