#include "console.h"

// System includes
#include <string>
#include <sstream>

// Glibrary includes
#include <Glibrary/console/log.h>

// Gengine includes
#include "../entity/entitytemplate.h"

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		void Console::Input(Player* player) {

			Log::Show();

			RunCommand(Log::Input(), player);

			Log::Hide();
		}

		void Console::RunCommand(const std::string& fullCommand, Player* player) {

			std::string copyOfFullCommand = fullCommand;

			std::string command = "";
			int num = 0;
			std::string entity = "";

			std::stringstream stringStream(copyOfFullCommand);

			stringStream >> command >> num >> entity;

			if (command == "") {
				return;
			}

			if (num <= 0) {
				copyOfFullCommand = fullCommand;

				//command = "";
				//entity = "";
				num = 1;

				std::stringstream newStringStream(copyOfFullCommand);

				newStringStream >> command >> entity;
			}

			if (command == "add") {
				for (int i = 0; i < num; i++) {

					if (!player->getInventory()->AddEntity(EntityTemplate::Find(entity))) {
						break;
					}
				}
				return;
			}

			if (command == "spawn") {
				for (int i = 0; i < num; i++) {
					if (!player->getLevel()->AddEntity(EntityTemplate::Find(entity), player->getPosition())) {
						break;
					}
				}
				return;
			}

			if (command == "godmode" || command == "Godmode" || command == "GODMODE" || command == "God mode" || command == "god mode") {
				player->ToggleInvincibility();
				return;
			}

			if (command == "all visible" || command == "supervision") {
				player->ToggleSuperVision();
				return;
			}

			if (command == "noclip" || command == "no clip") {
				player->ToggleNoClip();
				return;
			}

			if (command == "fuck") {
				Log::AddMessage("Eeew, you sick fuck!");
				return;
			}

			Log::AddMessage("There is no '" + command + "' command");

		}

	} // End namespace gengine
} // End namespace glaze