#pragma once
#include "Transform.h"
class Entity;

class Component
{
	Entity* m_pEntity;

public:

	void SetEntity(Entity* owner);
	virtual int GetID() = 0;

};

class MeshComponent : public Component
{
	static const int ID = 1;

public:
	int GetID() override { return ID; };
};

class TransformComponent : public Component
{
	TRANSFORM m_transform;
	static const int ID = 2;
public:

	void Move(float frontDir, float rightDir, float upDir);
	void GetPosition();

	int GetID() override { return ID; };
};
