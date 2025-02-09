#include "EntityTypes.h"

void EntityType::AddEntity()
{
	entityIDs.push_back(nextID++);
	//nextID++;
}

void EntityType::AddComponent(int componentIndex)
{
	switch (componentIndex)
	{
	case 0:
		Components.push_back(new TransformComponent);
			break;

	case 1:
		Components.push_back(new MeshComponent);
		break;

	case 2:
		Components.push_back(new Position);
		break;

	case 3:
		Components.push_back(new Velocity);
		break;

	default:
		break;

	}
}
