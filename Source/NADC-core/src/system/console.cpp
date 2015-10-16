#include "console.h"

// System includes
#include <string>
#include <sstream>

// Glibrary includes
#include <Glibrary/console/log.h>
#include <Glibrary/utils/utils.h>

// Gengine includes
#include "../entity/entitytemplate.h"
#include "../level/levelmanager.h"

namespace glaze {
	using namespace glibrary;
	namespace gengine {
		
		Player* Console::_player;
		Level* Console::_level;
		std::vector<std::string> Console::_commands;
		bool Console::_initialized;

		void Console::Init() {
			_commands.push_back("SPAWN 'integer(optional)' 'name of entity'; spawns entity at player position");
			_commands.push_back("ADD 'integer(optional)' 'name of entity'; add entity to inventory");
			_commands.push_back("GODMODE; toggles godmode");
			_commands.push_back("XRAY; toggles xray vision (sets all tiles/ entities visible)");
			_commands.push_back("NOCLIP; toggles noclip");
			_commands.push_back("DOWN/ D 'integer(optional)'; goes down one level");
			_commands.push_back("UP/ U 'integer(optional)'; moves player up one level");
		}

		void Console::Input(Player* player) {
			RunCommand(Log::Input(), player);
		}

		void Console::RunCommand(const std::string& fullCommand, Player* player) {
			
			if (fullCommand== "") return;

			if (_player == nullptr)
				_player = player;
			
			if (_level == nullptr)
				_level = player->getCurrentLevel();

			std::string command, entityName;
			int num = 0;

			std::stringstream(fullCommand) >> command >> num >> entityName; // Split command into its components
			
			// If integer is not defined default to 1
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

			if (command == "xray") {
				Commands::Xray();
				return;
			}

			if (command == "noclip") {
				Commands::NoClip();
				return;
			}

			if (command == "down" || command == "d") {
				Commands::GoDown(num);
				return;
			}

			if (command == "up" || command == "u") {
				Commands::GoUp(num);
				return;
			}

			if (command == "help") {
				Commands::Help();
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
				if (!_player->getCurrentLevel()->AddEntity(EntityTemplate::Find(entityName), _player->getPosition(), true)) {
					break;
				}
				x++;
			}

			Log::AddMessage("Added " + std::to_string(x) + " '" + entityName + "' to level");
		}

		void Console::Commands::Godmode() {
			_player->ToggleGodmode();
		}

		void Console::Commands::Xray() {
			_player->ToggleXray();
			_level->SetAllVisible();
		}

		void Console::Commands::NoClip() {
			_player->ToggleNoClip();
		}

		void Console::Commands::GoDown(const int& num) {
			for (int i = 0; i < num; i++)
				LevelManager::GoDown(_player);
		}

		void Console::Commands::GoUp(const int& num) {
			for (int i = 0; i < num; i++)
				LevelManager::GoUp(_player);
		}

		void Console::Commands::Help() {
			for (auto& command : _commands) {
				Log::AddMessage(command);
				Log::AddMessage("");
			}
		}

	} // End namespace gengine
} // End namespace glaze