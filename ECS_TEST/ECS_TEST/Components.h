#pragma once

#include <DirectXMath.h>
#include "Transform.h"

class Component
{
	//EntityID m_EntityID;


	//void SetEntity(EntityID* owner);
	//virtual int GetID() = 0;

};



class MeshComponent : public Component
{
};

class TransformComponent : public Component
{
	TRANSFORM m_transform;	
};

struct Velocity : public Component
{
	float vx, vy;
};