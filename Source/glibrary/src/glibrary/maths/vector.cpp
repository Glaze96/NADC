#include "vector.h"

// System includes
#include <math.h>

namespace glaze {
	namespace glibrary {

		template class Vector<int>;
		template class Vector<float>;

		template<class T>
		Vector<T>::Vector() {
			x = 0;
			y = 0;
		}

		template<class T>
		Vector<T>::Vector(T x, T y) {
			this->x = x;
			this->y = y;
		}

		template<class T>
		float Vector<T>::Mag() const {
			return (float)sqrt(x * x + y * y);
		}

		template<class T>
		Vector<T> Vector<T>::Normalized() const {
			Vector<T> normalized;
			normalized /= Mag();
			return normalized;

		}

		template<class T>
		std::string Vector<T>::ToString() const {
			return "(" + std::to_string(x) + "; " + std::to_string(y) + ")";
		}

		template<class T>
		Vector<T> Vector<T>::AngleToVector(const float& angle) {
			return Vector<T>();
		}

		template<class T>
		Vector<T> Vector<T>::operator+(const Vector<T>& v) const {
			return Vector<T>(x + v.x, y + v.y);
		}

		template<class T>
		Vector<T> Vector<T>::operator-(const Vector<T>& v) const {
			return Vector<T>(x - v.x, y - v.y);
		}

		template<class T>
		Vector<T> Vector<T>::operator+(const T& f) const {
			return Vector<T>(x + f, y + f);
		}

		template<class T>
		Vector<T> Vector<T>::operator-(const T& f) const {
			return Vector<T>(x - f, y - f);
		}

		template<class T>
		Vector<T> Vector<T>::operator*(const T& f) const {
			return Vector<T>(x * f, y * f);
		}

		template<class T>
		Vector<T> Vector<T>::operator/(const T& f) const {
			return Vector<T>(x / f, y / f);
		}

		template<class T>
		void Vector<T>::operator+=(const Vector<T>& v) {
			this->x += v.x;
			this->y += v.y;
		}

		template<class T>
		void Vector<T>::operator-=(const Vector<T>& v) {
			this->x -= v.x;
			this->y -= v.y;
		}

		template<class T>
		void Vector<T>::operator*=(const float& f) {
			this->x *= f;
			this->y *= f;
		}

		template<class T>
		void Vector<T>::operator/=(const float& f) {
			this->x /= f;
			this->y /= f;
		}

		template<class T>
		bool Vector<T>::operator==(const Vector<T>& v) const {
			if (x == v.x && y == v.y)
				return true;
			return false;
		}

		bool TestFunc() {
			return true;
		}

	} // End namespace glibrary
} // End namespace glaze