#pragma once

#include <string>

#include "vector2.h"
#include "constants.h"

namespace glaze {
	namespace glibrary {

		/* ____Box____ */

		class Boxi {
		public: // Public fields
			Vector2i Position;
			Vector2i Size;

		public: // public getters
			int getLeft() const { return Position.x; }
			int getTop() const { return Position.y; }
			int getRight() const { return Position.x + Size.x; }
			int getBottom() const { return Position.y + Size.y; }

			int getWidth() const { return Size.x; }
			int getHeight() const { return Size.y; }

			int getArea() const { return Size.x * Size.y; }

			Vector2f getCenter() const;

		public: // Con -& Destructurs
			Boxi();
			Boxi(const int& width, const int& height);
			Boxi(const int& width, const int& height, const int& top, const int& left);
			explicit Boxi(const Vector2i& size);
			Boxi(const Vector2i& position, const Vector2i& size);
			~Boxi() {}

		public: // Public methods
			std::string ToString() const;
			void Center(const Vector2i& center);
			void Center(const Vector2f& center);

		};

		/* ____Box____ */

		class Boxf {
		public: // Public fields
			Vector2f Position;
			Vector2f Size;

		public: // public getters
			float getLeft() const { return Position.x; }
			float getTop() const { return Position.y; }
			float getRight() const { return Position.x + Size.x; }
			float getBottom() const { return Position.y + Size.y; }

			float getWidth() const { return Size.x; }
			float getHeight() const { return Size.y; }

			float getArea() const { return Size.x * Size.y; }

			Vector2f getCenter() const;

		public: // Con -& Destructurs
			Boxf();
			Boxf(const float &width, const float &height, const float &top, const float &left);
			Boxf(const Vector2f &position, const Vector2f &size);
			~Boxf() {}

		public: // Public methods
			std::string ToString() const;

		};

		/* End ____Box____ */


		/* ____Circle____ */

		class Circle {
		public: // Public fields
			Vector2f Position;
			float Radius;

		public: // public getters
			float getDiameter() const { return Radius * 2; }

			float getLeft() const { return Position.x - Radius; }
			float getRight() const { return Position.x + Radius; }
			float getTop() const { return Position.y - Radius; }
			float getBottom() const { return Position.y + Radius; }

			float getArea() const { return 2 * PI * Radius; }

		public: // Con -& destructurs
			Circle();
			Circle(const float &x, const float &y, const float &radius);
			Circle(const Vector2f &position, const float &radius);
			~Circle() {}

		public: // Public methods
			std::string ToString() const;
		};

		/* End ____Circle____ */


		/* ____LineSegment____ */

		class LineSegment {
		public: // Public fields
			Vector2f PointA, PointB;

		public: // Public getters
			float getLength() const { return PointA.Mag() - PointB.Mag(); }

		public: // Con -& destructors
			LineSegment();
			LineSegment(const Vector2f& pointA, const Vector2f& pointB);
			~LineSegment() { }
		};

		/* End ____LineSegment____ */

		class Ray {
		public: // Public fields
			Vector2f Position, Direction;

		public:
			Ray();
			Ray(const Vector2f& position, const Vector2f& direction);
			~Ray() {}

		public: // Methods
			float getAngle() const;
		};


	} // End namespace glibrary
} // End namespace glaze