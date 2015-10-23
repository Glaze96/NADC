#pragma once

// System includes
#include <vector>

// Gengine includes
#include "newspawnsource.h"
#include <map>

namespace glaze {
	namespace gengine {

		class EntityTemplate {

		private: // Private fields
			static std::vector<std::pair<float, SpawnSource>> allSources;

			static std::vector<std::pair<float, SpawnSource>> newItemSources;
			static std::vector<std::pair<float, SpawnSource>> newSpecialItemSources;
			static std::vector<std::pair<float, SpawnSource>> newEnemySources;

		private: // 'structors
			EntityTemplate() { }

		public: // Public methods
			static void Init();

			static void UpdateSpawnChances(const int& levelNumber);
			
			static Entity* TryGetEntity(const float& randomNumber);

			static Entity* Find(const std::string& name);
		
		private: // Private methods
			static void SortSources();

		};

	} // End namespace gengine
} // End namespace glaze