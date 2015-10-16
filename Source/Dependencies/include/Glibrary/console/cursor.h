#pragma once

#include "window.h"
#include "..\..\curses\curses.h"

namespace glaze {
	namespace glibrary {

		class Cursor {
		public:
			static int LastXPosition;
			static int LastYPosition;

			static void Move(const int &x, const int &y);
			static void Move(const Window &window, const int &x, const int &y);
		
			static void Move(WINDOW *window, const int &x, const int &y);

		};

	} // End namespace glibrary
} // End na