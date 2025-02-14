#pragma once

#include <unordered_map>
#include <vector>
#include "Components.h"

//using Entity = uint32_t;
using ComponentMask = uint32_t;

enum ComponentType {
	COMPONENT_NONE = 0,
	COMPONENT_TRANSFORM = 1 << 0,
	COMPONENT_MESH = 1 << 1,

	COMPONENT_VELOCITY = 1 << 2,
	COMPONENT_HEALTH = 1 << 3,
	COMPONENT_HEAL = 1 << 4
};


class Entity
{
public:
	uint32_t id = 0;
	uint32_t tab_index = 0;
};

struct EntityComponents
{
	ComponentMask mask = 0;
	std::vector<Component*> components = { nullptr };
};


class EntityManager
{
public:

	/*std::unordered_map<Entity, ComponentMask>& GetEntityMap() {
		return entityComponents;
	}*/
	Entity*(&GetEntityTab())[64000]
	{
		return tab_entity;
	}
	EntityComponents*(&GetComponentsTab())[64000]
	{
		return tab_CompEntities;
	}

	// Cree une entite et retourne son ID
	Entity* CreateEntity();

	// Detruit une entite (supprime sa signature de composants)
	void DestroyEntity(Entity* entity);

	// Ajoute un composant a une entite (en "ou"-ant le bit)
	void AddComponent(Entity* entity, ComponentMask component);

	// Retire un composant a une entite (en effa�ant le bit)
	void RemoveComponent(Entity* entity, ComponentMask component);

	// Verifie si l'entite possede le(s) composant(s) indique(s)
	bool HasComponent(Entity* entity, ComponentMask component) const;

private:
	//Entity nextEntity = 1;
	uint32_t entityNb = 0;
	// Stocke pour chaque entite son bitmask de composants
	std::unordered_map<Entity, ComponentMask> entityComponents;

	EntityComponents* tab_CompEntities[64000] = { nullptr };

	Entity* tab_entity[64000] = { nullptr }; // 0 = pas d'entite   ---   1+ = entite ===> /!\ la premiere entite a l'index 1 /!\.
};