#pragma once

#include <DirectXMath.h>
#include "Transform.h"

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
	float vx, vy;
};