#pragma once

#include <string>

namespace glaze {
	namespace glibrary {

		class Message {
		public:
			enum Type {
				Normal,
				Warning,
				Error,
				Input,
				Success
			};

		private:

			std::string _string;
			Type _type;
			bool _visible;
			float _timer;
			int _position;

			Message(const std::string& s, const Type& type, const int& originalPosition);

			void Print();
			void Update(const float& updateTick);
			friend class Log;
		};


	} // End namespace gengine
} // End namespace glaze