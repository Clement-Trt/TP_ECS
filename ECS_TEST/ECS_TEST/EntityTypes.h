#pragma once

#include <vector>
#include "Components.h"

// Ou placer les entity Types ? Dans ECS ? Ou a part ?

namespace EntityTypes {

	using EntityID = uint32_t;

	// Archetype pour les entités qui ont Position et Velocity
	struct PNJs {
		std::vector<EntityID> entityIDs;
		std::vector<Components::Transformable> transformables;

		/*std::vector<Components::Position> positions;
		std::vector<Components::Velocity> velocities;*/
	};

	// Archetype pour les entités qui ont uniquement Velocity
	/*struct ArchetypeVelocityOnly {
		std::vector<EntityID> entityIDs;
		std::vector<Velocity> velocities;
	};*/
}