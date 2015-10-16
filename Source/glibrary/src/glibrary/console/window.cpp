#include "window.h"

#include "..\..\curses\curses.h"
#include "..\maths\geometry.h"
#include "..\graphics\draw.h"

#include <math.h>

namespace glaze {
	namespace glibrary {

		Window::Window() {

			_window = create(0, 0, 0, 0);

			_title = "New window";
		}
		
		Window::Window(char *title, const int &x, const int &y, const int &w, const int &h) {

			_position = Vector2i(x, y);
			_size = Vector2i(w, h);

			_window = create((float)w, (float)h, (float)x, (float)y);

			_title = title;
		}

		Window::~Window() {
			delwin(_window);
		}

		void Window::DrawBorders() {
			DrawBox(*this, Boxf((float)_size.x, (float)_size.y, 0, 0));
		}

		void Window::Center() {
			CenterX();
			CenterY();
		}

		void Window::CenterX() {

			int stdWidth = GetStdWindowWidth();

			_position.x = (int)((stdWidth / 2.0f) - (_size.x / 2.0f));
		}

		void Window::CenterY() {

			int stdHeight = GetStdWindowHeight();

			_position.y = (int)((stdHeight / 2.0f) - (_size.y / 2.0f));
		}

		void Window::Update() {

			delwin(_window);

			_window = create((float)_size.x, (float)_size.y, (float)_position.x, (float)_position.y);

			Refresh();
		}

		void Window::Refresh() {
			wrefresh(_window);
		}

		void Window::Clear() {
			wclear(_window);
		}

		void Window::Delete() {
			delwin(_window);
		}

		WINDOW* Window::create(const float &w, const float &h, const float &x, const float &y) {

			int stdWidth = GetStdWindowWidth();
			int stdHeight = GetStdWindowHeight();

			float newX = x;
			float newY = y;
			float newW = w;
			float newH = h;

			bool problem = false;

			if (x < 0) {
				newX = 0;
				newW = w + x;
			}

			if (y < 0) {
				newY = 0;
				newH = h + y;
			}

			if (x + w > stdWidth) {
				newW = stdWidth - x;
				problem = true;
			}

			if (y + h > stdHeight) {
				newH = stdHeight - y;
				problem = true;
			}

			return newwin((int)floor(newH), (int)floor(newW), (int)floor(newY), (int)floor(newX));
		}


	} // End namespace glibrary
} // End namespace glaze
