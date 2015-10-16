#include "message.h"

#include "io.h"
#include "../graphics/color.h"

namespace glaze {
	namespace glibrary {

		Message::Message(const std::string& s, const Type& type, const int& originalPosition)
			: _string(s), _type(type), _visible(true), _timer(2.0f), _position(originalPosition) {
		}

		void Message::Print() {
			if (_visible) {

				if (_type == Normal) {
					Color::SetColor(Color::WHITE);
				}
				else if (_type == Warning) {
					Color::SetColor(Color::YELLOW);
				}
				else if (_type == Error) {
					Color::SetColor(Color::RED);
					Color::SetBold();
				}
				else if (_type == Input) {
					Color::SetColor(Color::MAGENTA);
					Color::SetBold();
				}
				else if (_type == Success) {
					Color::SetColor(Color::GREEN);
				}

				Out::PrintlnAt(0, _position, _string);

				Color::ResetColor();
				Color::ResetBold();

			}
		}

		void Message::Update(const float& updateTick) {
			if (_timer > 0.0f)
				_timer -= updateTick;
			else
				_visible = false;
		}

	} // End namespace gengine
} // End namespace glaze