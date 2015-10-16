#include "geometry.h"

#include <string>

#include "vector2.h"

namespace glaze {
	namespace glibrary {

		/* ____Boxi____ */

		Boxi::Boxi() {
			Position = Vector2i();
			Size = Vector2i();
		}

		Boxi::Boxi(const int& width, const int& height) {
			Size.x = width;
			Size.y = height;
			Position = Vector2i();
		}

		Boxi::Boxi(const int &width, const int &height, const int &left, const int &top) {
			Size.x = width;
			Size.y = height;
			Position.x = left;
			Position.y = top;
		}

		Boxi::Boxi(const Vector2i& size) {
			Size = size;
			Position = Vector2i();
		}

		Boxi::Boxi(const Vector2i& position, const Vector2i& size) {
			Position = position;
			Size = size;
		}

		Vector2f Boxi::getCenter() const {
			return Position + Size / 2.0f;
		}

		std::string Boxi::ToString() const {
			return "Position: " + Position.ToString() + " Size: " + Size.ToString();
		}

		void Boxi::Center(const Vector2i& center) {
			Position = Vector2i(center.x - (int)(getWidth() / 2.0f), center.y - (int)(getHeight() / 2.0f));
		}

		void Boxi::Center(const Vector2f& center) {
			Center(Vector2i((int)floor(center.x), (int)floor(center.y)));
		}

		/* End ____Boxi____ */

		/* ____Boxf____ */

		Boxf::Boxf() {
			Position = Vector2f();
			Size = Vector2f();
		}

		Boxf::Boxf(const float &width, const float &height, const float &left, const float &top) {
			Size.x = width;
			Size.y = height;
			Position.x = left;
			Position.y = top;
		}

		Boxf::Boxf(const Vector2f &position, const Vector2f &size) {
			Position = position;
			Size = size;
		}

		Vector2f Boxf::getCenter() const {
			return Position + Size / 2.0f;
		}

		std::string Boxf::ToString() const {
			return "Position: " + Position.ToString() + " Size: " + Size.ToString();
		}

		/* End ____Boxf____ */


		/* ____Circle____ */

		Circle::Circle() {
			Position = Vector2f();
			Radius = 0.0f;
		}

		Circle::Circle(const float &x, const float &y, const float &radius) {
			Position = Vector2f(x, y);
			Radius = radius;
		}

		Circle::Circle(const Vector2f &position, const float &radius) {
			Position = position;
			Radius = radius;
		}

		std::string Circle::ToString() const {
			return "Position: " + Position.ToString() + " Radius: " + std::to_string(Radius);
		}

		/* End ____Circle____ */


		/* ____LineSegment____ */

		LineSegment::LineSegment() {
			PointA = Vector2f();
			PointB = Vector2f();
		}

		LineSegment::LineSegment(const Vector2f& pointA, const Vector2f& pointB) {
			PointA = pointA;
			PointB = pointB;
		}

		/* End ____LineSegment____ */

		Ray::Ray() {
			Position = Vector2f();
			Direction = Vector2f();
		}

		Ray::Ray(const Vector2f& position, const Vector2f& direction) {
			Position = position;
			Direction = direction;
		}

		float Ray::getAngle() const {
			return (float)atan2((float)Direction.y, (float)Direction.x);
		}

	} // End namespace glibrary
} // End namespace glaze