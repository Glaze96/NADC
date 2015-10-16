#include "draw.h"

#include "..\maths\geometry.h"
#include "..\maths\vector2.h"
#include "..\maths\constants.h"

#include <math.h>

namespace glaze {
	namespace glibrary {

		void DrawRectangle(Boxf &box, const char &ch) {

			Vector2i position((int)floor(box.Position.x), (int)floor(box.Position.y));
			Vector2i size((int)floor(box.Size.x), (int)floor(box.Size.y));

			for (int y = position.y; y < size.y + position.y; y++) {
				for (int x = position.x; x < size.x + position.x; x++) {

					mvaddch((int)(y * (8.0f / 12.0f)), x, ch);

				}
			}
		}

		void DrawBox(Boxf &box, const char &ch) {

			Vector2i position((int)floor(box.Position.x), (int)floor(box.Position.y));
			Vector2i size((int)floor(box.Size.x), (int)floor(box.Size.y));

			for (int y = position.y; y < size.y + position.y; y++) {
				for (int x = position.x; x < size.x + position.x; x++) {

					if ((y == position.y && x == position.x) ||
						(y == position.y && x == size.x + position.x - 1) ||
						(y == position.y + size.y - 1 && x == position.x) ||
						(y == position.y + size.y - 1 && x == position.x + size.x - 1)) {
						mvaddch(y, x, ch);
						continue;
					}

					if (y == position.y || y == position.y + size.y - 1) {
						mvaddch(y, x, ch);
					}
					else if (x == position.x || x == position.x + size.x - 1) {
						mvaddch(y, x, ch);
					}

				}
			}
		}

		void DrawBox(Boxf &box) {

			Vector2i position((int)floor(box.Position.x), (int)floor(box.Position.y));
			Vector2i size((int)floor(box.Size.x), (int)floor(box.Size.y));

			for (int y = position.y; y < size.y + position.y; y++) {
				for (int x = position.x; x < size.x + position.x; x++) {

					if ((y == position.y && x == position.x) ||
						(y == position.y && x == size.x + position.x - 1) ||
						(y == position.y + size.y - 1 && x == position.x) ||
						(y == position.y + size.y - 1 && x == position.x + size.x - 1)) {
						mvaddch(y, x, '+');
						continue;
					}

					if (y == position.y || y == position.y + size.y - 1) {
						mvaddch(y, x, '-');
					}
					else if (x == position.x || x == position.x + size.x - 1) {
						mvaddch(y, x, '|');
					}

				}
			}
		}

		void DrawBox(Window &window, Boxf &box) {

			Vector2i position((int)floor(box.Position.x), (int)floor(box.Position.y));
			Vector2i size((int)floor(box.Size.x), (int)floor(box.Size.y));

			for (int y = position.y; y < size.y + position.y; y++) {
				for (int x = position.x; x < size.x + position.x; x++) {

					if ((y == position.y && x == position.x) ||
						(y == position.y && x == size.x + position.x - 1) ||
						(y == position.y + size.y - 1 && x == position.x) ||
						(y == position.y + size.y - 1 && x == position.x + size.x - 1)) {
						mvwaddch(window.getWindow(), y, x, '+');
						continue;
					}

					if (y == position.y || y == position.y + size.y - 1) {
						mvwaddch(window.getWindow(), y, x, '-');
					}
					else if (x == position.x || x == position.x + size.x - 1) {
						mvwaddch(window.getWindow(), y, x, '|');
					}

				}
			}
		}

		void DrawBox(Window &window, Boxf &box, const char &ch) {

			Vector2i position((int)floor(box.Position.x), (int)floor(box.Position.y));
			Vector2i size((int)floor(box.Size.x), (int)floor(box.Size.y));

			for (int y = position.y; y < size.y + position.y; y++) {
				for (int x = position.x; x < size.x + position.x; x++) {

					if ((y == position.y && x == position.x) ||
						(y == position.y && x == size.x + position.x - 1) ||
						(y == position.y + size.y - 1 && x == position.x) ||
						(y == position.y + size.y - 1 && x == position.x + size.x - 1)) {
						mvwaddch(window.getWindow(), y, x, ch);
						continue;
					}

					if (y == position.y || y == position.y + size.y - 1) {
						mvwaddch(window.getWindow(), y, x, ch);
					}
					else if (x == position.x || x == position.x + size.x - 1) {
						mvwaddch(window.getWindow(), y, x, ch);
					}

				}
			}
		}

		void DrawCircle(Circle &circle) {

			float resolution = (8.0f / 12.0f) / circle.Radius;

			for (float angle = 0; angle < 2 * PI; angle += resolution) {

				Vector2f pos;

				pos.x = (circle.Radius * cos(angle)) + circle.Position.x;
				pos.y = (circle.Radius * sin(angle) * (8.0f / 12.0f)) + circle.Position.y;

				mvaddch((int)pos.y, (int)pos.x, 'o');

			}

		}

		void DrawCircle(Window &window, Circle &circle) {
			float resolution = (8.0f / 12.0f) / circle.Radius;

			for (float angle = 0; angle < 2 * PI; angle += resolution) {

				Vector2f pos;

				pos.x = (circle.Radius * cos(angle)) + circle.Position.x;
				pos.y = (circle.Radius * sin(angle) * (8.0f / 12.0f)) + circle.Position.y;

				mvwaddch(window.getWindow(), (int)pos.y, (int)pos.x, 'o');

			}

		}

		void DrawLineSegment(LineSegment &lineSegment) {

			Vector2f lineVector = lineSegment.PointB - lineSegment.PointA;

			float resolution = (8.0f / 12.0f) / lineVector.Mag();

			for (float point = 0; point < 1.0f; point += resolution) {

				Vector2f pos;

				pos.x = lineSegment.PointA.x + (point * lineVector.x);
				pos.y = lineSegment.PointA.y + (point * lineVector.y);

				mvaddch((int)pos.y, (int)pos.x, 'o');
			}

		}


	} // End namespace glibrary
} // End namespace glaze
