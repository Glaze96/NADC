#include "log.h"

#include <vector>
#include <string>

#include "io.h"
#include "../../curses/curses.h"
#include "../graphics/color.h"

namespace glaze {
	namespace glibrary {

		const unsigned int Log::_totalMessages = 98;
		std::vector<Message> Log::_messages;

		void Log::Update(const float &updateTick) {

			for (auto& message : _messages) {
				message.Update(updateTick);
			}
		}

		void Log::AddMessage(const std::string& msg, const Message::Type& type) {

			Message newMessage = Message(msg, type, _totalMessages);

			_messages.push_back(newMessage);

			if (_messages.size() > _totalMessages)
				DeleteFirstMessage();

			ShiftMessages(-1);

		}

		std::string Log::Input() {
			Color::SetColor(Color::MAGENTA);
			std::string input = In::ReadlnAt(0, _totalMessages);
			AddMessage(input, Message::Type::Input);
			return input;
		}

		void Log::Print() {
			for (unsigned int i = 0; i < _messages.size(); i++)
				_messages.at(i).Print();
		}

		void Log::DeleteFirstMessage() {
			_messages.erase(_messages.begin());
		}

		void Log::ShiftMessages(const int& direction) {
			for (auto& message : _messages) {
				message._position += direction;
			}
		}

		void Log::Show() {
			for (auto& message : _messages) {
				message._visible = true;
			}
			clear();
			Print();
			refresh();
		}

		void Log::Hide() {
			for (auto& message : _messages) {
				message._visible = false;
			}
		}

	} // End namespace gengine
} // End namespace glaze