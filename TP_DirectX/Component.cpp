#include "Component.h"
#include <iostream>

void Component::SetEntity(Entity* owner)
{
	m_pEntity = owner;
}
void TransformComponent::Move(float frontDir, float rightDir, float upDir)
{
	m_transform.Move(frontDir, rightDir, upDir);
}

void TransformComponent::GetPosition()
{
	std::cout << "Entity Position X = " << m_transform.GetPositionX() << "  Position Y = " << m_transform.GetPositionY() << "   Position Z = " << m_transform.GetPositionZ() << std::endl;
}

