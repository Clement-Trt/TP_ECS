#include "Movement.h"

void Movement::Initialize(/*GameManager* gameManager*/)
{
	//mGM = gameManager;
}

void Movement::SetVelocity(VelocityComponent* vc, float velX, float velY, float velZ)
{
	//VelocityComponent* vc = static_cast<VelocityComponent*>(mEM->GetComponentToAddTab()[0]->tab_components[Velocity_index]);
	vc->vz = velZ;
	vc->vx = velX;
	vc->vy = velY;
}
