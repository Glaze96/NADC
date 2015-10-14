#pragma once

#include <string>
#include <vector>

#include "message.h"

namespace glaze {
	namespace glibrary {

		class Log {
		private:
			const static unsigned int _totalMessages;
			static std::vector<Message> _messages;

		private:
			static void Update(const float &updateTick);
			static void Print();
			static void DeleteFirstMessage();
			static void ShiftMessages(const int& direction);

		public:
			static void Show();
			static void Hide();
			static void AddMessage(const std::string& msg, const Message::Type& severity = Message::Type::Normal);
			static std::string Input();

			friend class Engine;
		};


	} // End namespace gengine
} // End namespace glaze