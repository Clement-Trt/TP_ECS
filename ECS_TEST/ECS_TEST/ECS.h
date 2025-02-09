#pragma once

#include <vector>
#include <list>
#include <unordered_map>
#include "Components.h"
#include "EntityTypes.h"
#include"pch.h"

//using EntityID = uint32_t;

//class EntityTypes;

//
//namespace ECS
//{
//
//	class EntityManager {
//	private:
//		//EntityID nextID = 0;
//		std::vector<EntityID> entities;
//
//
//	public:
//		/*struct PNJs {
//			EntityID nextID = 0;
//			std::vector<EntityID> entityIDs;
//			std::vector<Components::Transformable> transformables;
//		};*/
//		EntityID createEntity();
//		EntityID createPNJEntity();
//		void destroyEntity(EntityID id);
//
//	};
//
//	class MovementSystem {
//	public:
//		void update(std::vector<Position>& positions,
//			std::vector<Velocity>& velocities,
//			float deltaTime);
//
//
//		/*TRANSFORM() { Identity(); };
//
//		void Identity();*/
//		/*void Update(std::vector<Components::Transformable>& transformables,
//			float deltaTime);*/
//		void Update(Transformable& transformable);
//
//		void Rotate(Transformable& transformable, float pitch, float yaw, float roll);
//		void Move(Transformable& transformable, float frontDir, float rightDir, float upDir);
//
//		/*float GetPositionX();
//		float GetPositionY();
//		float GetPositionZ();*/
//
//	};
//}
//

struct Entity {
	EntityID id;
	uint32_t componentMask; // Indique les composants que possède l'entité
};

class EntityManager {
private:
	//std::vector<EntityID> entities;
	std::vector<Entity*> entities;
	std::list<EntityID> entities;
	EntityID nextID = 0;
	std::vector<EntityType*> EntityTypesList;

public:

	EntityType* CreateNewEntityType();

	//EntityID CreateEntity(uint32_t componentMask);
	//EntityID createPNJEntity();

	void AddEntity(int entityType, uint32_t componentMask);
	void AddComponentToEntityType(int entityType, int componentIndex);

	void DestroyEntity(EntityID id);

};

class MovementSystem {
public:
	void update(std::vector<Position>& positions,
		std::vector<Velocity>& velocities,
		float deltaTime);

	/*void Update(Transformable& transformable);

	void Rotate(Transformable& transformable, float pitch, float yaw, float roll);
	void Move(Transformable& transformable, float frontDir, float rightDir, float upDir);*/


};