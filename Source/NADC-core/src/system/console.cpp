#include "console.h"

// System includes
#include <string>
#include <sstream>

// Glibrary includes
#include <Glibrary/console/log.h>

// Gengine includes
#include "../entity/entitytemplate.h"
#include "../level/levelmanager.h"

namespace glaze {
	using namespace glibrary;
	namespace gengine {
		
		Player* Console::_player;
		std::vector<std::string> Console::_commands;
		bool Console::_initialized;

		void Console::Input(Player* player) {
			RunCommand(Log::Input(), player);
		}

		void Console::RunCommand(const std::string& fullCommand, Player* player) {
			if (_player == nullptr)
				_player = player;

			std::string command, entityName;
			int num = 0;

			 std::stringstream(fullCommand) >> command >> num >> entityName; // Split command into its components

			if (command == "")
				return;

			if (num <= 0) {
				num = 1;
				std::stringstream(fullCommand) >> command >> entityName; // Split command into its components
			}

			if (command == "add") {
				Commands::Add(entityName, num);
				return;
			}

			if (command == "spawn") {
				Commands::Spawn(entityName, num);
				return;
			}

			if (command == "godmode") {
				Commands::Godmode();
				return;
			}

			if (command == "supervision") {
				Commands::SuperVision();
				return;
			}

			if (command == "noclip") {
				Commands::NoClip();
				return;
			}

			if (command == "down") {
				Commands::GoDown();
				return;
			}

			if (command == "up") {
				Commands::GoUp();
				return;
			}

			Log::AddMessage("There is no '" + command + "' command");

		}

		void Console::Commands::Add(const std::string& entityName, const int& num) {

			int x = 0;
			for (int i = 0; i < num; i++) {
				if (!_player->getInventory()->AddEntity(EntityTemplate::Find(entityName), true)) {
					break;
				}
				x++;
			}

			Log::AddMessage("Added " + std::to_string(x) + " '" + entityName + "' to inventory");
		}

		void Console::Commands::Spawn(const std::string& entityName, const int& num) {

			int x = 0;
			for (int i = 0; i < num; i++) {
				if (!_player->getLevel()->AddEntity(EntityTemplate::Find(entityName), _player->getPosition(), true)) {
					break;
				}
				x++;
			}

			Log::AddMessage("Added " + std::to_string(x) + " '" + entityName + "' to level");
		}

		void Console::Commands::Godmode() {
			_player->ToggleGodmode();
		}

		void Console::Commands::SuperVision() {
			_player->ToggleSuperVision();
		}

		void Console::Commands::NoClip() {
			_player->ToggleNoClip();
		}

		void Console::Commands::GoDown() {
			LevelManager::GoDown(_player);
		}

		void Console::Commands::GoUp() {
			LevelManager::GoUp(_player);
		}

	} // End namespace gengine
} // End namespace glaze