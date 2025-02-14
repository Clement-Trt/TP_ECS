#include "EntityManager.h"
#include <iostream>

Entity* EntityManager::CreateEntity() {
	//Entity* entity = nextEntity++;
	Entity* entity = new Entity;
	entity->tab_index = entityNb;
	entity->id = entityNb + 1;

	tab_entity[entity->tab_index] = entity; // Ajout de l'entity dans le tableau d'entities

	EntityComponents* newComponents = new EntityComponents;
	newComponents->mask = COMPONENT_NONE;
	newComponents->tab_index = entityNb;
	tab_CompEntities[entityNb] = newComponents; // Ajout des components (vides) de l'entity dans la case correspondant du tableau de composants
	// Pourquoi *newComponents et pas newComponents direct ?
	entityNb++;
	return entity;
}

void EntityManager::DestroyEntity(Entity* entity) {
	int index = entity->tab_index;
	int lastIndex = entityNb - 1;

	if (index > lastIndex) {
		std::cerr << "Index invalide." << std::endl;
		return;
	}

	tab_entity[lastIndex]->tab_index = index;
	*tab_entity[index] = *tab_entity[lastIndex];

	tab_CompEntities[lastIndex]->tab_index = index;
	*tab_CompEntities[index] = *tab_CompEntities[lastIndex];

	tab_entity[lastIndex] = nullptr;
	delete tab_entity[lastIndex];

	tab_CompEntities[lastIndex] = nullptr;
	delete tab_CompEntities[lastIndex];

	--entityNb;
}

void EntityManager::ToDestroy(Entity* entity)
{
	tab_todestroy.push_back(entity);
}

void EntityManager::AddComponent(Entity* entity, ComponentMask component) {
	tab_CompEntities[entity->tab_index]->mask |= component;

	//entityComponents[entity] |= component;

	switch (component)
	{
	case COMPONENT_TRANSFORM:
	{
		TransformComponent* newTransformComp = new TransformComponent;
		//tab_CompEntities[entity->tab_index]->components.push_back(newTransformComp);
		tab_CompEntities[entity->tab_index]->tab_components[Transform_index] = newTransformComp;
		break;
	}

	case COMPONENT_MESH:
	{
		MeshComponent* newMeshComp = new MeshComponent;
		//tab_CompEntities[entity->tab_index]->components.push_back(newMeshComp);
		tab_CompEntities[entity->tab_index]->tab_components[Mesh_index] = newMeshComp;
		break;
	}

	case COMPONENT_VELOCITY:
	{
		VelocityComponent* newVelocityComp = new VelocityComponent;
		//tab_CompEntities[entity->tab_index]->components.push_back(newVelocityComp);
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

void EntityManager::RemoveComponent(Entity* entity, ComponentMask component) {
	tab_CompEntities[entity->tab_index]->mask &= ~component;
	//entityComponents[entity] &= ~component;

	//int compIndex = 0;
	switch (component)
	{
	case COMPONENT_TRANSFORM:
	{
		//auto& component = tab_CompEntities[entity->tab_index]->components[Transform_index];
		auto& component = tab_CompEntities[entity->tab_index]->tab_components[Transform_index];

		if (component != nullptr)
		{
			delete component;
			component = nullptr;
		}
		break;
	}

	case COMPONENT_MESH:
	{
		auto& component = tab_CompEntities[entity->tab_index]->tab_components[Mesh_index];
		if (component != nullptr)
		{
			delete component;
			component = nullptr;
		}
		break;
	}

	case COMPONENT_VELOCITY:
		//tab_CompEntities[entity->tab_index]->tab_components.push_back(newVelocityComp);
		break;

	case COMPONENT_HEALTH:
		break;

	case COMPONENT_HEAL:
		break;


	default:
		break;
	}
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


