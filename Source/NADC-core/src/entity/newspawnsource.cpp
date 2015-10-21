#include "newspawnsource.h"

#include <Glibrary/utils/utils.h>

namespace glaze {
	namespace gengine {

		SpawnSource::SpawnSource(Entity* entity, const float& spawnChance)
			: _entity(entity), _spawnChance(spawnChance) {
			
			_name = _entity->getName();

			RemoveSpaces(_name);
		}

		Entity* SpawnSource::GetEntity() const {
			return _entity->newClone();
		}

	} // End namespace gengine
} // End namespace glaze