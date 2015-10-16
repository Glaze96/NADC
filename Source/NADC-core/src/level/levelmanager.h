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

			static Player* _player;

		private: // Con- & destructor's
			LevelManager() {}
			~LevelManager() {}

		public: // Public getters
			static const Level* getCurrentLevel() { return _currentLevel; }
			static const int& getNumLevels() { return _numLevels; }

		public: // Public methods
			static void Init(Player* player);
			static void GoUp(const bool& allVisible = false);
			static void GoDown(const bool& allVisible = false);
			static void PreLoadLevels(const int& num);
			static void Reset();

		private: // Private methods
			static void Clean();
			static void AddLevel();
			
		};

	} // End namespace gengine
} // End namespace glaze
