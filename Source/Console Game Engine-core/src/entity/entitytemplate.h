#pragma once

// System includes
#include <vector>

// Gengine includes
#include "newspawnsource.h"
#include <map>

namespace glaze {
	namespace gengine {

		class EntityTemplate {

		private: // Fields
			static std::map<std::string, SpawnSource> itemS;
			static std::map<std::string, SpawnSource> enemyS;
			static std::map<std::string, SpawnSource> specialItemS;

		private:
			EntityTemplate() { }

		public: // Methods
			static void UpdateSpawnChances(const int& levelNumber);
			static void Init();

			static Entity* TryGetItem(const int& randomNumber);
			static Entity* TryGetEnemy(const int& randomNumber);
			static Entity* Find(const std::string& name);

		};

	} // End namespace gengine
} // End namespace glaze