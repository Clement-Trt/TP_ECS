#pragma once

#include <vector>
#include <unordered_map>
#include "Components.h"

namespace ECS 
{
    using EntityID = uint32_t;

    class EntityManager {
    private:
        //EntityID nextID = 0;
        std::vector<EntityID> entities;


    public:
        /*struct PNJs {
            EntityID nextID = 0;
            std::vector<EntityID> entityIDs;
            std::vector<Components::Transformable> transformables;
        };*/
        EntityID createEntity();
        EntityID createPNJEntity();
        void destroyEntity(EntityID id);

    };

    class MovementSystem {
    public:
        void update(std::vector<Components::Position>& positions,
            std::vector<Components::Velocity>& velocities,
            float deltaTime);


        /*TRANSFORM() { Identity(); };

        void Identity();*/
        /*void Update(std::vector<Components::Transformable>& transformables,
            float deltaTime);*/
        void Update(Components::Transformable& transformable);

        void Rotate(Components::Transformable& transformable, float pitch, float yaw, float roll);
        void Move(Components::Transformable& transformable, float frontDir, float rightDir, float upDir);

        /*float GetPositionX();
        float GetPositionY();
        float GetPositionZ();*/

    };
}