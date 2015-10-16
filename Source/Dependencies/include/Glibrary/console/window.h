#pragma once

#include "..\..\curses\curses.h"
#include "..\maths\geometry.h"
#include "..\maths\vector2.h"

namespace glaze {
	namespace glibrary {

		class Window {

		public: // Private fields
			WINDOW *_window;
			char *_title;
			Vector2i _position;
			Vector2i _size;

		public: // Public fields
			static int GetStdWindowWidth() { return getmaxx(stdscr); }
			static int GetStdWindowHeight() { return getmaxy(stdscr); }
			
		public: //Constructors & Destructurs
			Window();
			Window(char *title, const int &x, const int &y, const int &w, const int &h);
			~Window();

		public: // Getters
			WINDOW *getWindow() const { return _window; }
			char *getTitle() const { return _title; }
			Vector2i getSize() const { return _size; }
			Vector2i getPosition() const { return _position; }
			int getWidth() const { return _size.x; }
			int getHeight() const { return _size.y; }
			int getX() const { return _position.x; }
			int getY() const { return _position.y; }

		public: // Public Methods
			void DrawBorders();
			void Center();
			void CenterX();
			void CenterY();
			void Update();
			void Refresh();
			void Clear();
			void Delete();

		private: // Private static functions
			WINDOW* create(const float &w, const float &h, const float &x, const float &y);


		};


	}
}