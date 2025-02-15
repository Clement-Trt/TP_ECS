#include "EntityManager.h"
#include <iostream>

Entity* EntityManager::CreateEntity() {

	Entity* entity = new Entity;
	entity->tab_index = entityNb;
	entity->id = entityNb + 1;

	tab_entity[entity->tab_index] = entity; // Ajout de l'entity dans le tableau d'entities

	EntityComponents* newComponents = new EntityComponents;
	newComponents->mask = COMPONENT_NONE;
	newComponents->tab_index = entityNb;
	tab_CompEntities[entityNb] = newComponents; // Ajout des components (vides) de l'entity dans la case correspondant du tableau de composants

	entityNb++;
	return entity;
}

int EntityManager::DestroyEntity(Entity* entity) {
	int index = entity->tab_index;
	int lastIndex = entityNb - 1;

	if (index > lastIndex) {
		std::cerr << "Index invalide." << std::endl;
		return 10000;
	}

	tab_entity[lastIndex]->tab_index = index;
	*tab_entity[index] = *tab_entity[lastIndex];

	tab_CompEntities[lastIndex]->tab_index = index;
	*tab_CompEntities[index] = *tab_CompEntities[lastIndex];

	tab_entity[lastIndex] = nullptr;
	delete tab_entity[lastIndex];

	tab_CompEntities[lastIndex] = nullptr;
	delete tab_CompEntities[lastIndex];
	int newEntityToPointAt =
		--entityNb;
	return entityNb;
}

void EntityManager::ToDestroy(Entity* entity)
{
	tab_toDestroy.push_back(entity);
}

void EntityManager::AddComponent(Entity* entity, ComponentMask component) {
	
	tab_CompEntities[entity->tab_index]->mask |= component;

	switch (component)
	{
	case COMPONENT_TRANSFORM:
	{
		TransformComponent* newTransformComp = new TransformComponent;
		tab_CompEntities[entity->tab_index]->tab_components[Transform_index] = newTransformComp;
		break;
	}

	case COMPONENT_MESH:
	{
		MeshComponent* newMeshComp = new MeshComponent;
		tab_CompEntities[entity->tab_index]->tab_components[Mesh_index] = newMeshComp;
		break;
	}

	case COMPONENT_VELOCITY:
	{
		VelocityComponent* newVelocityComp = new VelocityComponent;
		tab_CompEntities[entity->tab_index]->tab_components[Velocity_index] = newVelocityComp;
		break;
	}

	case COMPONENT_HEALTH:
		break;

	case COMPONENT_HEAL:
		break;

	default:
		break;
	}

}

void EntityManager::RemoveComponent(Entity* entity, ComponentMask componentMask) {
	
	tab_CompEntities[entity->tab_index]->mask &= ~componentMask;

	int compIndex = 0;
	switch (componentMask)
	{
	case COMPONENT_TRANSFORM:
		compIndex = Transform_index;
		break;

	case COMPONENT_MESH:
		compIndex = COMPONENT_MESH;
		break;

	case COMPONENT_VELOCITY:
		compIndex = COMPONENT_VELOCITY;
		break;

	case COMPONENT_HEALTH:
		compIndex = COMPONENT_HEALTH;
		break;

	case COMPONENT_HEAL:
		compIndex = COMPONENT_HEAL;
		break;

	default:
		break;
	}

	auto& component = tab_CompEntities[entity->tab_index]->tab_components[compIndex];

	if (component != nullptr)
	{
		delete component;
		component = nullptr;
	}
}

bool EntityManager::HasComponent(Entity* entity, ComponentMask component) const {

	return (tab_CompEntities[entity->tab_index]->mask & component) == component;
}


