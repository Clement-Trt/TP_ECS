#pragma once

//#include <DirectXMath.h>
#include "Transform.h"


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

class Component
{

};

class MeshComponent : public Component
{
};


//class PositionComponent : public Component
//{
	// /!\/!\/!\/!\/!\/!\/!\/!\/!\/!\  ---   Pourrait etre utilise pour optimiser l'utilisation : pas besoin du Transform entier tout le temps je pense ?   ---   /!\/!\/!\/!\/!\/!\/!\/!\/!\/!\
};


struct TransformComponent : public Component
{
	TRANSFORM m_transform;	
};

struct VelocityComponent : public Component
{
	float vz = 0.0f;
	float vx = 0.0f;
	float vy = 0.0f;
};