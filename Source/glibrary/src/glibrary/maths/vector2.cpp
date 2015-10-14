#include "vector2.h"

#include <string>

#include "constants.h"

namespace glaze {
	namespace glibrary {

		class Vector2i;

		// Constructors
		Vector2f::Vector2f() {
			x = 0.0f;
			y = 0.0f;
		}

		Vector2f::Vector2f(const Vector2i& vector) {
			x = (float)vector.x;
			y = (float)vector.y;
		}

		Vector2f::Vector2f(const float& p_x, const float& p_y) {
			x = p_x;
			y = p_y;
		}

		Vector2f::Vector2f(const int& p_x, const int& p_y) {
			x = (float)p_x;
			y = (float)p_y;
		}

		// Methods
		Vector2f Vector2f::Normalized() const {
			Vector2f normalized(*this);
			normalized /= Mag();
			return normalized;
		}

		float Vector2f::Mag() const {
			return (float)sqrt(x * x + y * y);
		}

		std::string Vector2f::ToString() const {
			return "(" + std::to_string(x) + "; " + std::to_string(y) + ")";
		}

		Vector2f Vector2f::AngleToVector(const float& angle) {
			float radians = angle * TO_RADIANS;
			Vector2f vector(cos(radians), sin(radians));
			return vector;
		}

		// Operators
		Vector2f Vector2f::operator+(const Vector2f& v) const {
			return Vector2f(x + v.x, y + v.y);
		}

		Vector2f Vector2f::operator+(const Vector2i& v) const {
			return Vector2f(x + (float)v.x, y + (float)v.y);
		}

		Vector2f Vector2f::operator-(const Vector2f& v) const {
			return Vector2f(x - v.x, y - v.y);
		}

		Vector2f Vector2f::operator-(const Vector2i& v) const {
			return Vector2f(x - (float)v.x, y - (float)v.y);
		}

		Vector2f Vector2f::operator+(const float& f) const {
			return Vector2f(x + f, y + f);
		}

		Vector2f Vector2f::operator-(const float& f) const {
			return Vector2f(x - f, y - f);
		}

		Vector2f Vector2f::operator*(const float& f) const {
			return Vector2f(x * f, y * f);
		}

		Vector2f Vector2f::operator/(const float& f) const {
			return Vector2f(x / f, x / f);
		}

		void Vector2f::operator+=(const Vector2f& v) {
			x += v.x;
			y += v.y;
		}

		void Vector2f::operator-=(const Vector2f& v) {
			x -= v.x;
			y -= v.y;
		}

		void Vector2f::operator*=(const float& f) {
			x *= f;
			y *= f;
		}

		void Vector2f::operator/=(const float& f) {
			x /= f;
			y /= f;
		}

		bool Vector2f::operator==(const Vector2f& v) const {
			if (x == v.x && y == v.y)
				return true;

			return false;
		}


		// Constructors
		Vector2i::Vector2i() {
			x = 0;
			y = 0;
		}

		Vector2i::Vector2i(const Vector2f& vector) {
			x = (int)floor(vector.x);
			y = (int)floor(vector.y);
		}

		Vector2i::Vector2i(const int& i) {
			x = i;
			y = i;
		}

		Vector2i::Vector2i(const int& p_x, const int& p_y) {
			x = p_x;
			y = p_y;
		}

		// Methods
		float Vector2i::Mag() const {
			return (float)sqrt(x * x + y * y);
		}

		Vector2f Vector2i::Normalized() const {
			Vector2f normalized(*this);
			normalized /= Mag();
			return normalized;
		}

		std::string Vector2i::ToString() const {
			return "(" + std::to_string(x) + "; " + std::to_string(y) + ")";
		}

		// Operators
		Vector2i Vector2i::operator+(const Vector2i& v) const {
			return Vector2i(x + v.x, y + v.y);
		}
		Vector2i Vector2i::operator-(const Vector2i& v) const {
			return Vector2i(x - v.x, y - v.y);
		}

		Vector2i Vector2i::operator+(const int& i) const {
			return Vector2i(x + i, y + i);
		}

		Vector2i Vector2i::operator*(const int& i) const {
			return Vector2i(x * i, y * i);
		}

		Vector2f Vector2i::operator+(const Vector2f& v) const {
			return Vector2f(x + v.x, y + v.y);
		}

		Vector2f Vector2i::operator-(const Vector2f& v) const {
			return Vector2f(x - v.x, y - v.y);
		}

		Vector2f Vector2i::operator+(const float& f) const {
			return Vector2f(x + f, y + f);
		}

		Vector2f Vector2i::operator-(const float& f) const {
			return Vector2f(x - f, y - f);
		}

		Vector2f Vector2i::operator*(const float& f) const {
			return Vector2f(x * f, y * f);
		}

		Vector2f Vector2i::operator/(const float& f) const {
			return Vector2f(x / f, y / f);
		}

		void Vector2i::operator+=(const Vector2i& v) {
			x += v.x;
			y += v.y;
		}

		void Vector2i::operator-=(const Vector2i& v) {
			x -= v.x;
			y -= v.y;
		}

		void Vector2i::operator*=(const int& i) {
			x *= i;
			y *= i;
		}

		void Vector2i::operator+=(const int& i) {
			x += i;
			y += i;
		}

		bool Vector2i::operator==(const Vector2i& v) const {
			if (x == v.x && y == v.y)
				return true;

			return false;
		}

	} // End namespace glibrary
} // End namespace glaze
