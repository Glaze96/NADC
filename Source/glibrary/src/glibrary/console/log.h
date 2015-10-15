#pragma once

#include <string>
#include <vector>

#include "message.h"

namespace glaze {
	namespace glibrary {

		class Log {
		private: // Private fields
			const static unsigned int _totalMessages;
			static std::vector<Message> _messages;

		public: // Public methods
			static void Show();
			static void Hide();
			static void AddMessage(const std::string& msg, const Message::Type& type = Message::Type::Normal);
			static std::string Input();
			static void Clean();

		private: // Private methods
			static void Update(const float &updateTick);
			static void Print();
			static void DeleteFirstMessage();
			static void ShiftMessages(const int& direction);

			friend class Engine;
		};


	} // End namespace gengine
} // End namespace glaze