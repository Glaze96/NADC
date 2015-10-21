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
			static std::vector<std::pair<float, SpawnSource>> newItemSources;

			static std::map<std::string, SpawnSource> itemSources;
			static std::map<std::string, SpawnSource> enemySources;
			static std::map<std::string, SpawnSource> specialItemSources;

		private: // 'structors
			EntityTemplate() { }

		public: // Public methods
			static void UpdateSpawnChances(const int& levelNumber);
			static Entity* TryGetItem(const float& randomNumber);
			static void Init();

			static Entity* TryGetEnemy(const int& randomNumber);
			static Entity* Find(const std::string& name);
		
		private: // Private methods
			static void SortSources();

		};

	} // End namespace gengine
} // End namespace glaze