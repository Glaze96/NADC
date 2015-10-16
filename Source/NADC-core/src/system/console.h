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
			static Level* _level;
			static std::vector<std::string> _commands;
			static bool _initialized;

		private: // Con- & destructor's
			Console() {}
			~Console() {}

		public: // Public methods
			static void Init();
			static void Input(Player* player);

		private: // Private methods
			static void RunCommand(const std::string& fullCommand);

			struct Commands {
				static void Add(const std::string& entityName, const int& num);
				static void Spawn(const std::string& entityName, const int& num);
				static void Godmode();
				static void Xray();
				static void NoClip();
				static void GoDown(const int& num);
				static void GoUp(const int& num);
				static void Help();
			};
		};

	}
}