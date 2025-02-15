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

	COMPONENT_HEAL = 1 << 4,		// Exemple

	TOTALCOMPONENT
};

enum ComponentIndex
{
	Transform_index,
	Mesh_index,
	Velocity_index,
	Health_index,

	Heal_index		// Exemple
};

class Entity
{
public:
	int32_t id = 0;
	uint32_t tab_index = 0;
};

struct EntityComponents
{
	uint32_t tab_index = 0;
	ComponentMask mask = 0;
	std::vector<Component*> components;
	Component* tab_components[TOTALCOMPONENT] = { nullptr };
};


class EntityManager
{
public:

	/*std::unordered_map<Entity, ComponentMask>& GetEntityMap() {
		return entityComponents;
	}*/
	Entity*(&GetEntityTab())[64000] { return tab_entity; }

	EntityComponents*(&GetComponentsTab())[64000] {	return tab_CompEntities; }

	std::vector<Entity*>& GetToDestroyTab() { return tab_toDestroy; }
	std::vector<Entity*>& GetEntityToAddTab() { return tab_entitiesToAdd; }
	std::vector<EntityComponents*>& GetComponentToAddTab() { return tab_compToAdd; }

	uint32_t GetNbEntity() { return entityNb; }

	// Cree une entite et retourne son ID
	Entity* CreateEntity();

	// Detruit une entite (supprime sa signature de composants)
	void ToDestroy(Entity* entity);
	int DestroyEntity(Entity* entity);

	// Ajoute un composant a une entite (en "ou"-ant le bit)
	void AddComponent(Entity* entity, ComponentMask component);

	// Retire un composant a une entite (en effaçant le bit)
	void RemoveComponent(Entity* entity, ComponentMask componentMask);

	// Verifie si l'entite possede le(s) composant(s) indique(s)
	bool HasComponent(Entity* entity, ComponentMask component) const;

	void AddEntityToTab(Entity* entity, EntityComponents* components);
	void ResetEntitiesToAdd() { entitiesToAddIndex = 0; }
private:

	uint32_t entityNb = 0; // Positif, ce sont les entity qui existent actuellement dans le jeu
	int32_t entitiesToAddIndex = 0; // Negatif pour savoir qu'elles ne sont pas encore ajoutées mais comme uint32_t peut pas etre neg => tres grand nombre

	EntityComponents* tab_CompEntities[64000] = { nullptr };

	Entity* tab_entity[64000] = { nullptr };

	//bool tab_todestroy[10000] = { false };
	//std::vector<bool> tab_todestroy = { false };
	std::vector<Entity*> tab_toDestroy;
	std::vector<Entity*> tab_entitiesToAdd ;
	std::vector<EntityComponents*> tab_compToAdd ;
};