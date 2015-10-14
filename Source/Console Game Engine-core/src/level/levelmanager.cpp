#include "levelmanager.h"
#include "level.h"

namespace glaze {
	namespace gengine {

		std::vector<Level*> LevelManager::_levels;
		Level* LevelManager::_currentLevel;
		int LevelManager::_numLevels = 0;
		int LevelManager::_currentLevelNumber = -1;

		void LevelManager::AddLevel(const bool& allVisible) {
			_levels.push_back(new Level(Vector2i(99, 99), allVisible));
			_numLevels++;
		}

		void LevelManager::GoUp(Player* player) {

			if (_currentLevelNumber > 0) {
				_currentLevelNumber--;
				_currentLevel = _levels[_currentLevelNumber];
				player->setLevel(_currentLevel);
				player->setPosition(_currentLevel->GetStairsDown()->getPosition());
				player->UpdateVisibility();
			}

		}

		void LevelManager::GoDown(Player* player) {

			_currentLevelNumber++;
			if (_numLevels <= _currentLevelNumber)
				AddLevel(player->getSuperVision());

			_currentLevel = _levels[_currentLevelNumber];
			
			player->setLevel(_currentLevel);
			player->setPosition(_currentLevel->GetStairsUp()->getPosition());
			player->UpdateVisibility();
		}

		void LevelManager::PreLoadLevels(const int& num) {
			for (int i = 0; i < num; i++) {
				AddLevel(false);
			}
		}

	} // End namespace gengine
} // End namespace glaze
