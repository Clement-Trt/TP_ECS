#pragma once

#include <DirectXMath.h>
#include "Transform.h"

//class Component
//{
//	EntityID m_EntityID;
//
//
//	//void SetEntity(EntityID* owner);
//	virtual int GetID() = 0;
//
//};



class MeshComponent
{
};

class TransformComponent
{
	TRANSFORM m_transform;	
};

struct Velocity 
{
	float vx, vy;
};