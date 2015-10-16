#include "newspawnsource.h"

namespace glaze {
	namespace gengine {

		SpawnSource::SpawnSource(Entity* entity, SpawnSource* lastSpawnSource, const float& spawnChance)
			: _entity(entity), _name(entity->getName()) {
			
			float lastSpawnChance = 0.0f;
			if (lastSpawnSource != nullptr)
				lastSpawnChance = lastSpawnSource->getSpawnChance();
			_spawnChance = lastSpawnChance + spawnChance;

		}

		Entity* SpawnSource::GetEntity() const {
			return _entity->newClone();
		}

	} // End namespace gengine
} // End namespace glaze