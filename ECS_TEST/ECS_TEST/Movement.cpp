#include "Movement.h"
#include "GameManager.h"
//#include "EntityManager.h"

void Movement::Initialize(GameManager* gameManager)
{
	mGM = gameManager;
}

void Movement::SetVelocity(Entity* entity, float velX, float velY, float velZ)
{
	VelocityComponent* vel = static_cast<VelocityComponent*>(mGM->GetEntityManager()->GetComponentToAddTab()[entity->tab_index]->tab_components[Velocity_index]);
	vel->vz = velZ;
	vel->vx = velX;
	vel->vy = velY;
}
