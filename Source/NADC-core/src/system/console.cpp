#include "console.h"

// System includes
#include <string>
#include <sstream>
#include <iterator>

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

			if (_player == nullptr)
				_player = player;

			_level = player->getCurrentLevel();

			RunCommand(Log::Input());
		}

		void Console::RunCommand(const std::string& fullCommand) {

			if (fullCommand == "") return;

			bool foundInteger = false;
			std::string command = "", entityName = "";
			int num = 1;

			std::istringstream ss(fullCommand);

			// http://stackoverflow.com/questions/236129/split-a-string-in-c
			std::vector<std::string> tokens{
				std::istream_iterator<std::string>{ss},
				std::istream_iterator<std::string>{}
			};

			// Gets command
			command = tokens[0];

			// Gets integer
			if (tokens.size() > 1) {
				if (IsInteger(tokens[1])) {
					num = std::stoi(tokens[1]);
					foundInteger = true;
				}
			}

			// Offsets index if no integer found
			int index = 0;
			if (foundInteger)
				index = 2;
			else
				index = 1;

			// Adds entity name
			for (; index < tokens.size(); index++) {
				entityName += tokens.at(index);
				if (index != tokens.size() - 1)
					entityName += " ";
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

			int i = 0;
			for (; i < num; i++) {
				if (!_player->getInventory()->Add(EntityTemplate::Find(entityName), true)) {
					break;
				}
			}

			Log::AddMessage("Added " + std::to_string(i) + " '" + entityName + "' to inventory");
		}

		void Console::Commands::Spawn(const std::string& entityName, const int& num) {

			int i = 0;
			for (; i < num; i++) {
				if (!_player->getCurrentLevel()->AddEntity(EntityTemplate::Find(entityName), _player->getPosition(), true)) {
					break;
				}
			}

			Log::AddMessage("Added " + std::to_string(i) + " '" + entityName + "' to level");
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
				LevelManager::GoDown(_player->getXray());
		}

		void Console::Commands::GoUp(const int& num) {
			for (int i = 0; i < num; i++)
				LevelManager::GoUp(_player->getXray());
		}

		void Console::Commands::Help() {
			for (auto& command : _commands) {
				Log::AddMessage(command);
				Log::AddMessage("");
			}
		}

	} // End namespace gengine
} // End namespace glaze