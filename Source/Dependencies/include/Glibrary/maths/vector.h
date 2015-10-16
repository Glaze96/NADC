#pragma once

#include <string>

namespace glaze {
	namespace glibrary {

		template<class T>
		class Vector {
		public:
			T x, y;

			Vector();
			Vector(T x, T y);
			~Vector() {}

		public: // Public methods
			float Mag() const;
			Vector<T> Normalized() const;
			std::string ToString() const;

		public: // Public static functions
			static Vector<T> AngleToVector(const float& angle);

		public: // Public operators
			Vector<T> operator+(const Vector<T>& v) const;
			Vector<T> operator-(const Vector<T>& v) const;

			Vector<T> operator+(const T& f) const;
			Vector<T> operator-(const T& f) const;
			Vector<T> operator*(const T& f) const;
			Vector<T> operator/(const T& f) const;

			void operator+=(const Vector<T>& v);
			void operator-=(const Vector<T>& v);
			void operator*=(const float& f);
			void operator/=(const float& f);

			bool operator==(const Vector<T>& v) const;
		};


	} // End namespace glibrary
} // End namespace glaze