#include "Entity.h"
#include "Component.h"
#include <iostream>

Entity::~Entity()
{
	for (auto* component : m_components)
	{
		delete component;
	}
}

bool Entity::AddComponent(Component* comp)
{
	int id = comp->GetID();
	for (auto* existingComponent : m_components)
	{
		if (id == existingComponent->GetID())
		{
			std::cout << "Component already added to Entity\n";
			return false;
		}
	}
	comp->SetEntity(this);
	m_components.push_back(comp);

	return true;
}


