#pragma once

#include <unordered_map>
#include "Components.h"

using Entity = uint32_t;
using ComponentMask = uint32_t;

enum ComponentType {
    COMPONENT_NONE = 0,
    COMPONENT_TRANSFORM = 1 << 0, // 0x01
    COMPONENT_MESH = 1 << 1, // 0x02

    COMPONENT_VELOCITY = 1 << 2, // 0x03
    COMPONENT_HEALTH = 1 << 3 // 0x04
};

class EntityManager {
public:

    Entity(&GetEntityTab())[64000] {
        return tab_entity;
    }
    /*ComponentMask (&GetEntityComponentsTab())[64000] {
        return tab_entityComponents;
    }*/

    // Cree une entite et retourne son ID
    Entity CreateEntity();

    // Detruit une entite (supprime sa signature de composants)
    void DestroyEntity(Entity entity);

    // Ajoute un composant a une entite (en "ou"-ant le bit)
    void AddComponent(Entity entity, ComponentMask component);

    // Retire un composant a une entite (en effaçant le bit)
    void RemoveComponent(Entity entity, ComponentMask component);

    // Verifie si l'entite possede le(s) composant(s) indique(s)
    bool HasComponent(Entity entity, ComponentMask component) const;

private:
    Entity nextEntity = 1;
    // Stocke pour chaque entite son bitmask de composants
    std::unordered_map<Entity, ComponentMask> entityComponents;

    //ComponentMask tab_entityComponents[64000] = { 0 };

    Entity tab_entity[64000] = { 0 };

    //int entityListSize = 64000;
};