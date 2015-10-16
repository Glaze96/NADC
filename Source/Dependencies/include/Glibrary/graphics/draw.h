#pragma once

#include "..\maths\geometry.h"
#include "..\console\window.h"

namespace glaze {
	namespace glibrary {


		extern void DrawRectangle(Boxf &box, const char &ch);
		// Add w rectangle
		extern void DrawBox(Boxf &box);
		extern void DrawBox(Boxf &box, const char &ch);
		extern void DrawBox(Window &window, Boxf &box);
		extern void DrawBox(Window &window, Boxf &box, const char &ch);

		extern void DrawCircle(Circle &circle);
		extern void DrawCircle(Window &window, Circle &circle);

		extern void DrawLineSegment(LineSegment &lineSegment);
		// Add w linesegment

	} // End namespace glibrary
} // End namespace glaze