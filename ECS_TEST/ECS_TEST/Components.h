#pragma once

#include <DirectXMath.h>
#include "pch.h"
#include "Transform.h"

constexpr uint32_t COMPONENT_TRANSFORM = 1 << 0; // 0x01
constexpr uint32_t COMPONENT_MESH = 1 << 1; // 0x02
constexpr uint32_t COMPONENT_POSITION = (1 << 1) + (1 << 0); // 0x03
constexpr uint32_t COMPONENT_VELOCITY = (1 << 2); // 0x04
constexpr uint32_t COMPONENT_HEALTH = (1 << 2) + (1 << 0); // 0x05

class Component
{
	EntityID m_EntityID;


	void SetEntity(EntityID* owner);
	virtual int GetID() = 0;

};



class MeshComponent : public Component
{
	static const int ID = 1;

	int GetID() override { return ID; };
};

class TransformComponent : public Component
{
	TRANSFORM m_transform;
	static const int ID = 2;

	void Move(float frontDir, float rightDir, float upDir);
	void GetPosition();

	int GetID() override { return ID; };
};


//_________________________________TEST ____________________________________

struct Position : public Component
{
	static const int ID = 3;
	float x, y;

	int GetID() override { return ID; };
};

struct Velocity : public Component
{
	static const int ID = 4;
	float vx, vy;

	int GetID() override { return ID; };
};