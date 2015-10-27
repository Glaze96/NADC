#include "levelmanager.h"
#include "level.h"

namespace glaze {
	namespace gengine {

		std::vector<Level*> LevelManager::_levels;
		Level* LevelManager::_currentLevel;
		int LevelManager::_numLevels = 0;
		int LevelManager::_currentLevelNumber = -1;
		Player* LevelManager::_player;

		void LevelManager::Init(Player* player) {
			_player = player;
			GoDown();
		}

		void LevelManager::GoUp(const bool& allVisible) {

			if (_currentLevelNumber > 0) {
				_currentLevelNumber--;
				_currentLevel = _levels[_currentLevelNumber];
				_player->setLevel(_currentLevel);
				_player->setPosition(_currentLevel->GetStairsDown()->getPosition());
				_player->UpdateVisibility();
				_player->DispatchPlayerMovedEvent(Vector2i());
				if (allVisible)
					_currentLevel->SetAllVisible();

			}
		}

		void LevelManager::GoDown(const bool& allVisible) {
			_currentLevelNumber++;

			if (_numLevels <= _currentLevelNumber)
				AddLevel();

			_currentLevel = _levels[_currentLevelNumber];
			
			_player->setLevel(_currentLevel);
			_player->setPosition(_currentLevel->GetStairsUp()->getPosition());
			_player->UpdateVisibility();
			_player->DispatchPlayerMovedEvent(Vector2i());

			if (allVisible)
				_currentLevel->SetAllVisible();
		}

		void LevelManager::PreLoadLevels(const int& num) {
			for (int i = 0; i < num; i++) {
				AddLevel();
			}
		}

		void LevelManager::Reset() {
			_numLevels = 0;
			_currentLevelNumber = -1;
			Clean();
			GoDown();
		}

		void LevelManager::Clean() {
			for (auto* level : _levels) {
				delete level;
			}
			_levels.clear();
		}

		void LevelManager::AddLevel() {
			_levels.push_back(new Level(Vector2i(99, 99)));
			_numLevels++;
		}

	} // End namespace gengine
} // End namespace glaze
