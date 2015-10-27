#pragma once

#include "..\maths\geometry.h"

namespace glaze {
	namespace glibrary {

		class Draw {
		public:
			static void DrawBox(Boxf &box);
			static void DrawBox(Boxf &box, const char &ch);

			static void DrawCircle(Circle &circle);

			static void DrawLineSegment(LineSegment &lineSegment);

		};

	} // End namespace glibrary
} // End namespace glaze