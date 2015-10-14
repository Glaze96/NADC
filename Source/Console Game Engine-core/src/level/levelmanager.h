#pragma once

// System includes
#include <vector>

// Gengine includes
#include "../entity/creature/player.h"

namespace glaze {
	namespace gengine {
		
		class Level;

		class LevelManager {
		private: // Private fields
			static std::vector<Level*> _levels;
			static Level* _currentLevel;
			static int _numLevels;
			static int _currentLevelNumber;

		private: // Con- & destructors
			LevelManager() {}
			~LevelManager() {}

		public: // Public getters
			static Level* getCurrentLevel() { return _currentLevel; }
			static int getNumLevels() { return _numLevels; }

		public: // Public methods
			static void GoUp(Player* player);
			static void GoDown(Player* player);
			static void PreLoadLevels(const int& num);

		private: // Private methods
			static void AddLevel(const bool& allVisible);
			
		};

	} // End namespace gengine
} // End namespace glaze
