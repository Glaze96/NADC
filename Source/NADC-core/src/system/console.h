#pragma once

// System includes
#include <string>

// Gengine includes
#include "../entity/creature/player.h"

namespace glaze {
	namespace gengine {
		class Console {
		private: // Private fields
			static Player* _player;
			static std::vector<std::string> _commands;
			static bool _initialized;

		private: // Con- & destructor's
			Console() {}
			~Console() {}

		public: // Public static methods
			static void Init();
			static void Input(Player* player);

		private: // Private static methods
			static void RunCommand(const std::string& command, Player* player);

			struct Commands {
				static void Add(const std::string& entityName, const int& num);
				static void Spawn(const std::string& entityName, const int& num);
				static void Godmode();
				static void SuperVision();
				static void NoClip();
				static void GoDown(const int& num);
				static void GoUp(const int& num);
				static void Help();
			};
		};

	}
}